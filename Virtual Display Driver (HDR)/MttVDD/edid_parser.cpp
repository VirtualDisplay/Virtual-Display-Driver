#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <fstream>
#include <stdio.h>
#include <set>

namespace EdidParser {

using MonitorMode = std::tuple<int, int, int, int>; // (x_res, y_res, refresh_rate, divider)

static void add_vic_resolution(uint8_t vic, std::vector<MonitorMode>& modes) {
    // Complete VIC table from CEA-861 (up to latest, e.g., CEA-861-J)
    // Refresh rate as integer (Hz), divider adjusts to precise rate (e.g., 1001 for 59.94 Hz)
    switch (vic) {
        case 1: modes.push_back({640, 480, 60, 1}); break;      // 640x480@60p
        case 2: modes.push_back({720, 480, 60, 1001}); break;   // 720x480@59.94p
        case 3: modes.push_back({720, 480, 60, 1}); break;      // 720x480@60p
        case 4: modes.push_back({1280, 720, 60, 1}); break;     // 1280x720@60p
        case 5: modes.push_back({1920, 1080, 60, 1001}); break; // 1920x1080@59.94i
        case 6: modes.push_back({720, 480, 60, 1001}); break;   // 720x480@59.94i (1440x480i)
        case 7: modes.push_back({720, 480, 60, 1}); break;      // 720x480@60i (1440x480i)
        case 8: modes.push_back({720, 240, 60, 1001}); break;   // 720x240@59.94p
        case 9: modes.push_back({720, 240, 60, 1}); break;      // 720x240@60p
        case 10: modes.push_back({1440, 480, 60, 1001}); break; // 1440x480@59.94i
        case 11: modes.push_back({1440, 480, 60, 1}); break;    // 1440x480@60i
        case 12: modes.push_back({1440, 240, 60, 1001}); break; // 1440x240@59.94p
        case 13: modes.push_back({1440, 240, 60, 1}); break;    // 1440x240@60p
        case 14: modes.push_back({1440, 480, 60, 1001}); break; // 1440x480@59.94p
        case 15: modes.push_back({1440, 480, 60, 1}); break;    // 1440x480@60p
        case 16: modes.push_back({1920, 1080, 60, 1}); break;   // 1920x1080@60p
        case 17: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50p
        case 18: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50i (1440x576i)
        case 19: modes.push_back({1280, 720, 50, 1}); break;    // 1280x720@50p
        case 20: modes.push_back({1920, 1080, 50, 1}); break;   // 1920x1080@50i
        case 21: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50i (1440x576i)
        case 22: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50p
        case 23: modes.push_back({720, 288, 50, 1}); break;     // 720x288@50p
        case 24: modes.push_back({720, 288, 50, 1}); break;     // 720x288@50p
        case 25: modes.push_back({1440, 576, 50, 1}); break;    // 1440x576@50i
        case 26: modes.push_back({1440, 288, 50, 1}); break;    // 1440x288@50p
        case 27: modes.push_back({1440, 288, 50, 1}); break;    // 1440x288@50p
        case 28: modes.push_back({1440, 576, 50, 1}); break;    // 1440x576@50p
        case 29: modes.push_back({1440, 576, 50, 1}); break;    // 1440x576@50p
        case 30: modes.push_back({1920, 1080, 50, 1}); break;   // 1920x1080@50p
        case 31: modes.push_back({1920, 1080, 100, 1}); break;  // 1920x1080@100p
        case 32: modes.push_back({1920, 1080, 24, 1}); break;   // 1920x1080@24p
        case 33: modes.push_back({1920, 1080, 25, 1}); break;   // 1920x1080@25p
        case 34: modes.push_back({1920, 1080, 30, 1}); break;   // 1920x1080@30p
        case 35: modes.push_back({720, 480, 120, 1}); break;    // 720x480@120p
        case 36: modes.push_back({720, 480, 120, 1}); break;    // 720x480@120i
        case 37: modes.push_back({720, 240, 120, 1}); break;    // 720x240@120p
        case 38: modes.push_back({1440, 480, 120, 1}); break;   // 1440x480@120i
        case 39: modes.push_back({1440, 480, 120, 1}); break;   // 1440x480@120p
        case 40: modes.push_back({720, 576, 100, 1}); break;    // 720x576@100p
        case 41: modes.push_back({720, 576, 100, 1}); break;    // 720x576@100i
        case 42: modes.push_back({720, 288, 100, 1}); break;    // 720x288@100p
        case 43: modes.push_back({1440, 576, 100, 1}); break;   // 1440x576@100i
        case 44: modes.push_back({1440, 576, 100, 1}); break;   // 1440x576@100p
        case 45: modes.push_back({720, 480, 200, 1}); break;    // 720x480@200p
        case 46: modes.push_back({720, 480, 200, 1}); break;    // 720x480@200i
        case 47: modes.push_back({720, 240, 200, 1}); break;    // 720x240@200p
        case 48: modes.push_back({1440, 480, 200, 1}); break;   // 1440x480@200i
        case 49: modes.push_back({1440, 480, 200, 1}); break;   // 1440x480@200p
        case 50: modes.push_back({720, 576, 200, 1}); break;    // 720x576@200p
        case 51: modes.push_back({720, 576, 200, 1}); break;    // 720x576@200i
        case 52: modes.push_back({720, 288, 200, 1}); break;    // 720x288@200p
        case 53: modes.push_back({1440, 576, 200, 1}); break;   // 1440x576@200i
        case 54: modes.push_back({1440, 576, 200, 1}); break;   // 1440x576@200p
        case 55: modes.push_back({720, 480, 240, 1}); break;    // 720x480@240p
        case 56: modes.push_back({720, 480, 240, 1}); break;    // 720x480@240i
        case 57: modes.push_back({720, 240, 240, 1}); break;    // 720x240@240p
        case 58: modes.push_back({1440, 480, 240, 1}); break;   // 1440x480@240i
        case 59: modes.push_back({1440, 480, 240, 1}); break;   // 1440x480@240p
        case 60: modes.push_back({1280, 720, 24, 1}); break;    // 1280x720@24p
        case 61: modes.push_back({1280, 720, 25, 1}); break;    // 1280x720@25p
        case 62: modes.push_back({1280, 720, 30, 1}); break;    // 1280x720@30p
        case 63: modes.push_back({1920, 1080, 120, 1}); break;  // 1920x1080@120p
        case 64: modes.push_back({1920, 1080, 120, 1}); break;  // 1920x1080@120i
        case 65: modes.push_back({1280, 720, 120, 1}); break;   // 1280x720@120p
        case 66: modes.push_back({720, 480, 60, 1001}); break;  // 720x480@59.94p (alt)
        case 67: modes.push_back({720, 480, 60, 1}); break;     // 720x480@60p (alt)
        case 68: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50p (alt)
        case 69: modes.push_back({1280, 720, 60, 1001}); break; // 1280x720@59.94p
        case 70: modes.push_back({1280, 720, 24, 1001}); break; // 1280x720@23.976p
        case 71: modes.push_back({1920, 1080, 60, 1001}); break;// 1920x1080@59.94p
        case 72: modes.push_back({1920, 1080, 24, 1001}); break;// 1920x1080@23.976p
        case 73: modes.push_back({1920, 1080, 30, 1001}); break;// 1920x1080@29.97p
        case 74: modes.push_back({2880, 480, 60, 1001}); break; // 2880x480@59.94i
        case 75: modes.push_back({2880, 480, 60, 1}); break;    // 2880x480@60i
        case 76: modes.push_back({2880, 576, 50, 1}); break;    // 2880x576@50i
        case 77: modes.push_back({2880, 576, 50, 1}); break;    // 2880x576@50p
        case 78: modes.push_back({1920, 1080, 30, 1001}); break;// 1920x1080@29.97i
        case 79: modes.push_back({1920, 1080, 60, 1}); break;   // 1920x1080@60i
        case 80: modes.push_back({1280, 720, 30, 1001}); break; // 1280x720@29.97p
        case 81: modes.push_back({720, 480, 60, 1001}); break;  // 720x480@59.94p (alt 2)
        case 82: modes.push_back({720, 480, 60, 1}); break;     // 720x480@60p (alt 2)
        case 83: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50p (alt 2)
        case 84: modes.push_back({720, 480, 120, 1}); break;    // 720x480@120p (alt)
        case 85: modes.push_back({720, 576, 100, 1}); break;    // 720x576@100p (alt)
        case 86: modes.push_back({720, 480, 240, 1}); break;    // 720x480@240p (alt)
        case 87: modes.push_back({720, 576, 200, 1}); break;    // 720x576@200p (alt)
        case 88: modes.push_back({720, 480, 60, 1001}); break;  // 720x480@59.94i (alt)
        case 89: modes.push_back({720, 480, 60, 1}); break;     // 720x480@60i (alt)
        case 90: modes.push_back({720, 576, 50, 1}); break;     // 720x576@50i (alt)
        case 91: modes.push_back({1920, 1080, 24, 1001}); break;// 1920x1080@23.976p (alt)
        case 92: modes.push_back({1920, 1080, 30, 1}); break;   // 1920x1080@30p (alt)
        case 93: modes.push_back({3840, 2160, 24, 1}); break;   // 3840x2160@24p
        case 94: modes.push_back({3840, 2160, 25, 1}); break;   // 3840x2160@25p
        case 95: modes.push_back({3840, 2160, 30, 1}); break;   // 3840x2160@30p
        case 96: modes.push_back({3840, 2160, 50, 1}); break;   // 3840x2160@50p
        case 97: modes.push_back({3840, 2160, 60, 1}); break;   // 3840x2160@60p
        case 98: modes.push_back({4096, 2160, 24, 1}); break;   // 4096x2160@24p
        case 99: modes.push_back({4096, 2160, 25, 1}); break;   // 4096x2160@25p
        case 100: modes.push_back({4096, 2160, 30, 1}); break;  // 4096x2160@30p
        case 101: modes.push_back({4096, 2160, 50, 1}); break;  // 4096x2160@50p
        case 102: modes.push_back({4096, 2160, 60, 1}); break;  // 4096x2160@60p
        case 103: modes.push_back({3840, 2160, 24, 1001}); break;// 3840x2160@23.976p
        case 104: modes.push_back({3840, 2160, 30, 1001}); break;// 3840x2160@29.97p
        case 105: modes.push_back({3840, 2160, 60, 1001}); break;// 3840x2160@59.94p
        case 106: modes.push_back({4096, 2160, 24, 1001}); break;// 4096x2160@23.976p
        case 107: modes.push_back({4096, 2160, 30, 1001}); break;// 4096x2160@29.97p
        case 108: modes.push_back({4096, 2160, 60, 1001}); break;// 4096x2160@59.94p
        case 109: modes.push_back({3840, 2160, 120, 1}); break; // 3840x2160@120p
        case 110: modes.push_back({3840, 2160, 100, 1}); break; // 3840x2160@100p
        case 111: modes.push_back({4096, 2160, 120, 1}); break; // 4096x2160@120p
        case 112: modes.push_back({4096, 2160, 100, 1}); break; // 4096x2160@100p
        case 113: modes.push_back({7680, 4320, 24, 1}); break;  // 7680x4320@24p
        case 114: modes.push_back({7680, 4320, 25, 1}); break;  // 7680x4320@25p
        case 115: modes.push_back({7680, 4320, 30, 1}); break;  // 7680x4320@30p
        case 116: modes.push_back({7680, 4320, 50, 1}); break;  // 7680x4320@50p
        case 117: modes.push_back({7680, 4320, 60, 1}); break;  // 7680x4320@60p
        case 118: modes.push_back({7680, 4320, 24, 1001}); break;// 7680x4320@23.976p
        case 119: modes.push_back({7680, 4320, 30, 1001}); break;// 7680x4320@29.97p
        case 120: modes.push_back({7680, 4320, 60, 1001}); break;// 7680x4320@59.94p
        case 121: modes.push_back({7680, 4320, 120, 1}); break; // 7680x4320@120p
        case 122: modes.push_back({7680, 4320, 100, 1}); break; // 7680x4320@100p
        default: break; // Unknown VIC, skip
    }
}

static void parse_cea861_block(const uint8_t* block, std::vector<MonitorMode>& modes) {
    uint8_t dtd_start = block[2];
    if (dtd_start == 0) return;

    int offset = 4;
    while (offset < dtd_start) {
        uint8_t len_type = block[offset++];
        uint8_t len = len_type & 0x1F;
        uint8_t type = len_type >> 5;
        if (type == 2) { // Video Data Block
            for (int i = 0; i < len; ++i) {
                uint8_t vic = block[offset + i];
                add_vic_resolution(vic, modes);
            }
        }
        offset += len;
    }

    offset = dtd_start;
    while (offset < 128 && block[offset] != 0x00) {
        int x_res = ((block[offset + 4] & 0xF0) << 4) | block[offset + 2];
        int y_res = ((block[offset + 7] & 0xF0) << 4) | block[offset + 5];
        uint32_t pixel_clock = (block[offset + 1] << 8) | block[offset]; // in 10 kHz
        int refresh_rate = static_cast<int>((pixel_clock * 10000.0f) / (x_res * y_res) + 0.5f);
        int divider = (refresh_rate == 60 || refresh_rate == 30 || refresh_rate == 24) ? 1001 : 1;
        modes.push_back({x_res, y_res, refresh_rate, divider});
        offset += 18;
    }
}

static void parse_displayid_block(const uint8_t* block, std::vector<MonitorMode>& modes) {
    int offset = 3;
    while (offset < 128) {
        uint8_t type = block[offset++];
        if (type == 0x00) break;
        uint8_t len = block[offset++];
        if (type == 0x02) { // Type 1 Timing
            int x_res = ((block[offset + 1] & 0x0F) << 8) | block[offset];
            int y_res = ((block[offset + 3] & 0x0F) << 8) | block[offset + 2];
            int refresh_rate = block[offset + 4];
            int divider = (refresh_rate == 60 || refresh_rate == 30 || refresh_rate == 24) ? 1001 : 1;
            modes.push_back({x_res, y_res, refresh_rate, divider});
        }
        offset += len;
    }
}

static void parse_base_block(const uint8_t* edid_data, std::vector<MonitorMode>& modes) {
    for (int i = 38; i < 54; i += 2) {
        uint8_t byte1 = edid_data[i];
        uint8_t byte2 = edid_data[i + 1];
        if (byte1 == 0x01 && byte2 == 0x01) continue;

        int x_res = (byte1 + 31) * 8;
        int aspect = (byte2 >> 6) & 0x03;
        int y_res;
        switch (aspect) {
            case 0: y_res = x_res * 3 / 4; break;
            case 1: y_res = x_res * 9 / 16; break;
            case 2: y_res = x_res * 10 / 16; break;
            case 3: y_res = x_res; break;
        }
        int refresh_rate = (byte2 & 0x3F) + 60;
        int divider = (refresh_rate == 60) ? 1001 : 1;
        modes.push_back({x_res, y_res, refresh_rate, divider});
    }

    for (int i = 54; i < 126; i += 18) {
        if (edid_data[i] == 0x00 && edid_data[i + 1] == 0x00) continue;

        int x_res = ((edid_data[i + 4] & 0xF0) << 4) | edid_data[i + 2];
        int y_res = ((edid_data[i + 7] & 0xF0) << 4) | edid_data[i + 5];
        uint32_t pixel_clock = (edid_data[i + 1] << 8) | edid_data[i]; // in 10 kHz
        int refresh_rate = static_cast<int>((pixel_clock * 10000.0f) / (x_res * y_res) + 0.5f);
        int divider = (refresh_rate == 60 || refresh_rate == 30 || refresh_rate == 24) ? 1001 : 1;
        modes.push_back({x_res, y_res, refresh_rate, divider});
    }
}

std::vector<MonitorMode> parse_edid(const uint8_t* edid_data, size_t size) {
    std::vector<MonitorMode> modes;

    if (size < 128 || edid_data[0] != 0x00 || edid_data[1] != 0xFF || edid_data[2] != 0xFF ||
        edid_data[3] != 0xFF || edid_data[4] != 0xFF || edid_data[5] != 0xFF || edid_data[6] != 0xFF ||
        edid_data[7] != 0x00) {
        throw std::runtime_error("Invalid EDID header");
    }

    parse_base_block(edid_data, modes);

    uint8_t ext_count = edid_data[126];
    if (size < 128 * (ext_count + 1)) {
        throw std::runtime_error("EDID data too short for extension blocks");
    }

    for (uint8_t i = 0; i < ext_count; ++i) {
        const uint8_t* ext_block = edid_data + 128 * (i + 1);
        switch (ext_block[0]) {
            case 0x02: parse_cea861_block(ext_block, modes); break;
            case 0x10: parse_displayid_block(ext_block, modes); break;
            default: break;
        }
    }

    // Deduplicate modes
    std::set<MonitorMode> uniqueModes(modes.begin(), modes.end());
    modes.assign(uniqueModes.begin(), uniqueModes.end());

    return modes;
}

std::vector<MonitorMode> load_and_parse_edid(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open EDID file");
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> edid_data(size);
    file.read(reinterpret_cast<char*>(edid_data.data()), size);
    return parse_edid(edid_data.data(), size);
}

} // namespace EdidParser