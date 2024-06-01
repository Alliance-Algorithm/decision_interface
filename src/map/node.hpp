#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace type {
enum class NodeType {
    NONE,
    BLOCK,
    USED,
    AVAILABLE,
};

struct Node {
    int x;
    int y;
    int8_t value;
    NodeType type;
};

class NodeMap {
public:
    NodeMap(size_t width, size_t length)
        : width_(width)
        , length_(length)
    {
        reset();
    }

    void reset()
    {
        data_.resize(length_ * width_);
        for (auto x = 0; x < width_; x++)
            for (auto y = 0; y < length_; y++) {
                auto& node = data_[x + y * width_];
                node.type  = type::NodeType::NONE;
                node.value = 0;
                node.x     = x;
                node.y     = y;
            }
    }

    /// @param x 0 ~ width-1
    /// @param y 0 ~ length-1
    auto& operator()(size_t x, size_t y)
    {
        assert(x < width_);
        assert(y < length_);

        return data_[x + y * width_];
    }

    auto& operator*()
    {
        return data_;
    }

private:
    std::vector<Node> data_;
    size_t width_;
    size_t length_;
};
} // namespace type