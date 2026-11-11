
#pragma once

#include <cstddef>
#include <utility>
#include <vector>

#include "x86agent/perception/observation.hpp"
#include "x86agent/reasoning/reasoning_engine.hpp"

namespace x86agent::kernel {

struct AnalysisReport {
    perception::Observation observation;
    std::vector<reasoning::Finding> findings;

    [[nodiscard]] std::size_t finding_count() const noexcept {
        return findings.size();
    }

    [[nodiscard]] bool has_critical_findings() const noexcept {
        for (const auto& finding : findings) {
            if (finding.severity == reasoning::Severity::Critical) {
                return true;
            }
        }

        return false;
    }
};

class Kernel {
public:
    explicit Kernel(
        const reasoning::ReasoningEngine& reasoning_engine
    ) noexcept
        : reasoning_engine_(reasoning_engine) {}

    [[nodiscard]] AnalysisReport analyze(
        const perception::Observation& observation
    ) const {

        AnalysisReport report;

        report.observation = observation;
        report.findings = reasoning_engine_.analyze(observation);

        return report;
    }

private:
    const reasoning::ReasoningEngine& reasoning_engine_;
};

} // namespace x86agent::kernel
