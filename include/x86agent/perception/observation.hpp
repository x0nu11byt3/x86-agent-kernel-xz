
#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace x86agent::perception {

enum class ProcessState {
    Running,
    Stopped,
    Exited,
    Unknown
};

struct Observation {
    std::uint64_t process_id{0};

    ProcessState process_state{
        ProcessState::Unknown
    };

    // General-purpose and control registers.
    std::unordered_map<std::string, std::uint64_t> registers;

    // Current instruction address and mnemonic.
    std::uint64_t instruction_pointer{0};
    std::string current_instruction;

    // Stack snapshot represented as memory addresses.
    std::vector<std::uint64_t> stack;

    // Observation metadata.
    std::string architecture{"x86_64"};
    std::string source{"simulated"};
};

} // namespace x86agent::perception
