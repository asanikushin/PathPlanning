#include "astar.h"


Astar::Astar(double HW, bool BT) {
    hweight = HW;
    breakingties = BT;
}

double Astar::computeHFromCellToCell(int i1, int j1, int i2, int j2, const EnvironmentOptions &options) const {
    if (options.metrictype == CN_SP_MT_EUCL) {
        return (sqrt((i2 - i1) * (i2 - i1) + (j2 - j1) * (j2 - j1)));
    }

    if (options.metrictype == CN_SP_MT_CHEB) {
        return std::max(std::abs(i1 - i2), std::abs(j1 - j2));
    }

    if (options.metrictype == CN_SP_MT_DIAG) {
        double diag_section = std::abs(std::abs(i1 - i2) - std::abs(j1 - j2));
        double side_section = sqrt(2) * std::min(std::abs(i1 - i2), std::abs(j1 - j2));
        return diag_section + side_section;
    }

    if (options.metrictype == CN_SP_MT_MANH) {
        return std::abs(i1 - i2) + std::abs(j1 - j2);
    }
    return 0;
}
