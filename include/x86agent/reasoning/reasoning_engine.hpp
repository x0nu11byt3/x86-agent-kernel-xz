
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "x86agent/perception/observation.hpp"

namespace x86agent::reasoning {

enum class Severity {
    Info,
    Warning,
    Critical
};

struct Finding {
    std::string rule_id;
    Severity severity{Severity::Info};
    std::string description;
    std::string evidence;
};

class ReasoningEngine {
public:
    virtual ~ReasoningEngine() = default;

    virtual std::vector<Finding> analyze(
        const perception::Observation& observation
    ) const = 0;
};

class SymbolicReasoningEngine final : public ReasoningEngine {
public:
    std::vector<Finding> analyze(
        const perception::Observation& observation
    ) const override {

        std::vector<Finding> findings;

        const auto& registers = observation.registers;

        // Rule 1: Missing instruction pointer.
        const auto rip = registers.find("rip");

        if (rip == registers.end()) {
            findings.push_back({
                "X86-001",
                Severity::Warning,
                "Instruction pointer register is unavailable.",
                "The observation does not contain RIP."
            });
        } else if (rip->second == 0) {
            findings.push_back({
                "X86-002",
                Severity::Critical,
                "Instruction pointer is zero.",
                "RIP = 0x0"
            });
        }

        // Rule 2: Missing stack pointer.
        const auto rsp = registers.find("rsp");

        if (rsp == registers.end()) {
            findings.push_back({
                "X86-003",
                Severity::Warning,
                "Stack pointer register is unavailable.",
                "The observation does not contain RSP."
            });
        } else if (rsp->second == 0) {
            findings.push_back({
                "X86-004",
                Severity::Critical,
                "Stack pointer is zero.",
                "RSP = 0x0"
            });
        }

        // Rule 3: Missing instruction information.
        if (observation.current_instruction.empty()) {
            findings.push_back({
                "X86-005",
                Severity::Info,
                "Instruction information is unavailable.",
                "No instruction mnemonic was provided."
            });
        }

        // Rule 4: Empty stack snapshot.
        if (observation.stack.empty()) {
            findings.push_back({
                "X86-006",
                Severity::Info,
                "Stack snapshot is empty.",
                "No stack entries were provided."
            });
        }

        return findings;
    }
};

} // namespace x86agent::reasoning
