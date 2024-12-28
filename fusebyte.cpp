/******************************************************************************
 * File Name    : fusebyte.cpp
 * Coder        : Aziz Gökhan NARİN
 * E-Mail       : azizgokhannarin@yahoo.com
 * Explanation  : Perfect Bit Sequence
 * Versiyon     : 1.0.0
 ******************************************************************************/

#include "fusebyte.h"

#include <iostream>
#include <algorithm>

FuseByte::FuseByte()
{

}

FuseByte::~FuseByte()
{

}

std::vector<bool> FuseByte::fuse(const std::vector<std::vector<bool>> &bitSets)
{
    if (bitSets.empty()) {
        return {};
    }

    std::vector<bool> unusedFlags(bitSets.size(), true);

    int idx1, idx2, initialBestPosition;

    if (!findInitialPair(bitSets, idx1, idx2, initialBestPosition)) {
        return (bitSets.size() == 1) ? bitSets[0] : std::vector<bool> {};
    }

    std::vector<bool> mergedSeq = createMergedSequence(bitSets[idx1], bitSets[idx2], initialBestPosition);
    unusedFlags[idx1] = false;
    unusedFlags[idx2] = false;

    std::unordered_map<int, std::vector<int>> bitsetPositions;

    removeContainedBitsetsInMergedSeq(mergedSeq, bitSets, unusedFlags, bitsetPositions);
    mainFusionLoop(mergedSeq, bitSets, unusedFlags, bitsetPositions);
    optimizeRedundancies(mergedSeq, bitSets, unusedFlags, bitsetPositions);

    return mergedSeq;
}

bool FuseByte::findInitialPair(const std::vector<std::vector<bool>> &bitSets, int &idx1, int &idx2,
                               int &initialBestPosition)
{
    int numBitsets = static_cast<int>(bitSets.size());
    int maxOverlap = -1;
    idx1 = idx2 = -1;
    initialBestPosition = 0;

    for (int i = 0; i < numBitsets; ++i) {
        for (int j = i + 1; j < numBitsets; ++j) {
            int bestPosition = 0;
            int overlap = computeMaxOverlap(bitSets[i], bitSets[j], bestPosition);
            if (overlap > maxOverlap) {
                maxOverlap = overlap;
                idx1 = i;
                idx2 = j;
                initialBestPosition = bestPosition;
            }
        }
    }

    return (idx1 != -1 && idx2 != -1);
}

std::vector<bool> FuseByte::createMergedSequence(const std::vector<bool> &bitsetA, const std::vector<bool> &bitsetB,
        int positionB)
{
    int newStart = std::min(0, positionB);
    int newEnd = std::max(static_cast<int>(bitsetA.size()), positionB + static_cast<int>(bitsetB.size()));

    std::vector<bool> mergedSeq(newEnd - newStart);

    for (size_t i = 0; i < bitsetA.size(); ++i) {
        int pos = static_cast<int>(i) - newStart;
        mergedSeq[pos] = bitsetA[i];
    }

    for (size_t i = 0; i < bitsetB.size(); ++i) {
        int pos = positionB + static_cast<int>(i) - newStart;
        mergedSeq[pos] = bitsetB[i];
    }

    return mergedSeq;
}

void FuseByte::removeContainedBitsetsInMergedSeq(std::vector<bool> &mergedSeq,
        const std::vector<std::vector<bool>> &bitSets, std::vector<bool> &unusedFlags,
        std::unordered_map<int, std::vector<int>> &bitsetPositions)
{
    int numBitsets = static_cast<int>(bitSets.size());
    for (int i = 0; i < numBitsets; ++i) {
        if (unusedFlags[i]) {
            std::vector<int> occ = findOccurrences(mergedSeq, bitSets[i]);
            if (!occ.empty()) {
                unusedFlags[i] = false;
                bitsetPositions[i] = occ;
            }
        }
    }
}

void FuseByte::mainFusionLoop(std::vector<bool> &mergedSeq, const std::vector<std::vector<bool>> &bitSets,
                              std::vector<bool> &unusedFlags, std::unordered_map<int, std::vector<int>> &bitsetPositions)
{
    int numBitsets = static_cast<int>(bitSets.size());

    while (std::count(unusedFlags.begin(), unusedFlags.end(), true) > 0) {
        int bestIdx = -1;
        int bestPosition = 0;
        int maxOverlap = -1;

        for (int i = 0; i < numBitsets; ++i) {
            if (unusedFlags[i]) {
                int pos = 0;
                int overlap = computeMaxOverlap(mergedSeq, bitSets[i], pos);
                if (overlap > maxOverlap) {
                    maxOverlap = overlap;
                    bestIdx = i;
                    bestPosition = pos;
                }
            }
        }

        if (bestIdx == -1) {
            break;
        }

        mergedSeq = mergeBitset(mergedSeq, bitSets[bestIdx], bestPosition);

        unusedFlags[bestIdx] = false;
        bitsetPositions[bestIdx] = findOccurrences(mergedSeq, bitSets[bestIdx]);

        for (int i = 0; i < numBitsets; ++i) {
            if (unusedFlags[i]) {
                std::vector<int> occ = findOccurrences(mergedSeq, bitSets[i]);
                if (!occ.empty()) {
                    unusedFlags[i] = false;
                    bitsetPositions[i] = occ;
                }
            }
        }
    }
}

std::vector<bool> FuseByte::mergeBitset(const std::vector<bool> &mergedSeq, const std::vector<bool> &newBitset,
                                        int position)
{
    int newStart = std::min(0, position);
    int newEnd = std::max(static_cast<int>(mergedSeq.size()), position + static_cast<int>(newBitset.size()));
    std::vector<bool> newMerged(newEnd - newStart);

    for (size_t i = 0; i < mergedSeq.size(); ++i) {
        int pos = static_cast<int>(i) - newStart;
        newMerged[pos] = mergedSeq[i];
    }

    for (size_t i = 0; i < newBitset.size(); ++i) {
        int pos = position + static_cast<int>(i) - newStart;
        newMerged[pos] = newBitset[i];
    }

    return newMerged;
}

void FuseByte::optimizeRedundancies(std::vector<bool> &mergedSeq, const std::vector<std::vector<bool>> &bitSets,
                                    const std::vector<bool> &unusedFlags, std::unordered_map<int, std::vector<int>> &bitsetPositions)
{
    for (auto &kv : bitsetPositions) {
        int bIdx = kv.first;
        auto &occurrences = kv.second;

        if (occurrences.size() > 1) {
            for (size_t occIdx = 0; occIdx < occurrences.size(); ++occIdx) {
                int pos = occurrences[occIdx];
                int bitLen = static_cast<int>(bitSets[bIdx].size());

                std::vector<bool> tempMerged = mergedSeq;

                tempMerged.erase(tempMerged.begin() + pos,
                                 tempMerged.begin() + pos + bitLen);

                if (allBitsetsContained(tempMerged, bitSets, unusedFlags)) {
                    mergedSeq = tempMerged;

                    for (auto &kv2 : bitsetPositions) {
                        for (auto &p : kv2.second) {
                            if (p > pos) {
                                p -= bitLen;
                            }
                        }
                    }

                    occurrences.erase(occurrences.begin() + occIdx);
                    occIdx--;

                    if (occurrences.size() <= 1) {
                        break;
                    }
                }
            }
        }
    }
}

int FuseByte::computeMaxOverlap(const std::vector<bool> &mergedSeq, const std::vector<bool> &bitsetVec,
                                int &bestPosition)
{
    int maxOverlap = -1;
    bestPosition = 0;

    int mergedLength = static_cast<int>(mergedSeq.size());
    int bitsetLength = static_cast<int>(bitsetVec.size());

    for (int pos = -bitsetLength + 1; pos < mergedLength; ++pos) {
        int overlap = 0;
        bool conflict = false;

        for (int i = 0; i < bitsetLength; ++i) {
            int mergedIdx = pos + i;
            if (mergedIdx >= 0 && mergedIdx < mergedLength) {
                if (mergedSeq[mergedIdx] == bitsetVec[i]) {
                    overlap++;
                } else {
                    conflict = true;
                    break;
                }
            }
        }

        if (!conflict && overlap > maxOverlap) {
            maxOverlap = overlap;
            bestPosition = pos;
        }
    }

    return maxOverlap;
}

std::vector<int> FuseByte::findOccurrences(const std::vector<bool> &mergedSeq,
        const std::vector<bool> &bitsetVec)
{
    std::vector<int> positions;
    int mergedLength = static_cast<int>(mergedSeq.size());
    int bitsetLength = static_cast<int>(bitsetVec.size());

    for (int pos = 0; pos <= mergedLength - bitsetLength; ++pos) {
        bool match = true;

        for (int i = 0; i < bitsetLength; ++i) {
            if (mergedSeq[pos + i] != bitsetVec[i]) {
                match = false;
                break;
            }
        }

        if (match) {
            positions.push_back(pos);
        }
    }

    return positions;
}

bool FuseByte::allBitsetsContained(const std::vector<bool> &tempMerged,
                                   const std::vector<std::vector<bool>> &bitsetVecs,
                                   const std::vector<bool> &unusedFlags)
{
    int mergedLength = static_cast<int>(tempMerged.size());
    int n = static_cast<int>(bitsetVecs.size());

    for (int i = 0; i < n; ++i) {
        if (!unusedFlags[i]) {
            bool found = false;
            int bitLen = static_cast<int>(bitsetVecs[i].size());
            for (int pos = 0; pos <= mergedLength - bitLen; ++pos) {
                bool match = true;
                for (int j = 0; j < bitLen; ++j) {
                    if (tempMerged[pos + j] != bitsetVecs[i][j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return false;
            }
        }
    }

    return true;
}
