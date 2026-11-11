
#include <cstdint>
#include <iomanip>
#include <iostream>

#include "x86agent/kernel/kernel.hpp"
#include "x86agent/reasoning/reasoning_engine.hpp"

namespace {

const char* to_string(x86agent::reasoning::Severity severity) {
    using x86agent::reasoning::Severity;

    switch (severity) {
        case Severity::Info:
            return "INFO";

        case Severity::Warning:
            return "WARNING";

        case Severity::Critical:
            return "CRITICAL";
    }

    return "UNKNOWN";
}

void print_report(
    const x86agent::kernel::AnalysisReport& report
) {
    const auto& observation = report.observation;

    std::cout << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "        XZ  X86 Agent Kernel\n";
    std::cout << "----------------------------------------\n";

    std::cout << "Architecture: " << observation.architecture << '\n';
    std::cout << "Process ID:   " << observation.process_id << '\n';
    std::cout << "Source:       " << observation.source << '\n';

    std::cout << "\n[ EXECUTION CONTEXT ]\n";

    std::cout << "RIP: 0x"
              << std::hex
              << observation.instruction_pointer
              << std::dec << '\n';

    std::cout << "Instruction: "
              << observation.current_instruction << '\n';

    std::cout << "\n[ REASONING RESULTS ]\n";

    if (report.findings.empty()) {
        std::cout << "No findings detected.\n";
    }

    for (const auto& finding : report.findings) {
        std::cout << "\n"
                  << '[' << to_string(finding.severity) << "] "
                  << finding.rule_id << '\n';

        std::cout << "Description: "
                  << finding.description << '\n';

        std::cout << "Evidence:    "
                  << finding.evidence << '\n';
    }

    std::cout << "\n[ SUMMARY ]\n";

    std::cout << "Total findings: "
              << report.finding_count() << '\n';

    std::cout << "Critical findings: "
              << (report.has_critical_findings() ? "YES" : "NO")
              << '\n';

    std::cout << "------------------------------------------\n";
}

} // namespace

int main() {

    // 1. Initialize the reasoning engine.
    x86agent::reasoning::SymbolicReasoningEngine reasoning_engine;

    // 2. Initialize the agent kernel.
    x86agent::kernel::Kernel kernel(reasoning_engine);

    // 3. Build a simulated x86-64 execution observation.
    x86agent::perception::Observation observation;

    observation.process_id = 1337;

    observation.process_state =
        x86agent::perception::ProcessState::Stopped;

    observation.architecture = "x86_64";
    observation.source = "simulated";

    observation.registers = {
        {"rip", 0x00007fffffffd120ULL},
        {"rsp", 0x00007fffffffd000ULL},
        {"rbp", 0x00007fffffffd080ULL},
        {"rax", 0x0000000000000001ULL},
        {"rbx", 0x0000000000000000ULL}
    };

    observation.instruction_pointer =
        0x00007fffffffd120ULL;

    observation.current_instruction = "mov eax, 1";

    observation.stack = {
        0x00007fffffffd080ULL,
        0x00007fffffffd0a0ULL,
        0x00007fffffffd100ULL
    };

    // 4. Execute the analysis cycle.
    const auto report = kernel.analyze(observation);

    // 5. Display the analysis report.
    print_report(report);

    return report.has_critical_findings() ? 1 : 0;
}
