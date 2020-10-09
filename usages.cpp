#ifndef _WIN32

#include "usages.h"

long parseLineStatus(char *line) {
    // This assumes that a digit will be found and the line ends in " Kb".
    size_t i = strlen(line);
    const char *p = line;
    while (*p < '0' || *p > '9') {
        p++;
    }
    line[i - 3] = '\0';
    long val = strtol(p, nullptr, 10);
    return val;
}

long getRamMemoryUsage() { //Note: this value is in KB!
    FILE *file = fopen("/proc/self/status", "r");
    long result = -1;
    char line[128];

    while (fgets(line, 128, file) != nullptr) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            result = parseLineStatus(line);
            break;
        }
    }
    fclose(file);
    return result;
}

long getVirMemoryUsage() { //Note: this value is in KB!
    FILE *file = fopen("/proc/self/status", "r");
    long result = -1;
    char line[128];

    while (fgets(line, 128, file) != nullptr) {
        if (strncmp(line, "VmSize:", 7) == 0) {
            result = parseLineStatus(line);
            break;
        }
    }
    fclose(file);
    return result;
}

void printMem() {
    return;
    std::cerr << getRamMemoryUsage() / 1024. / 1024. << "\t" << getVirMemoryUsage() / 1024. / 1024. << "\n";
}


#endif