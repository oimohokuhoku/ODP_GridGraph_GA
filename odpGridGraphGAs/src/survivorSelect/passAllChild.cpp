#include "passAllChild.hpp"

#include <utility>
#include "../group.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;

Group PassAllChild::select(const Group& childs, const Group& parents) {
    return std::move(childs);
}