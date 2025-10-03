/******************************************************************************
 * File Name    : fusebyte.h
 * Coder        : Aziz Gökhan NARİN
 * E-Mail       : azizgokhannarin@yahoo.com
 * Explanation  : Perfect Bit Sequence
 * Versiyon     : 1.0.0
 ******************************************************************************/

#ifndef FUSEBYTE_H
#define FUSEBYTE_H

#include <cinttypes>
#include <vector>
#include <unordered_map>

class FuseByte
{
public:
    explicit FuseByte();
    virtual ~FuseByte();

    std::vector<bool> fuse(const std::vector<std::vector<bool>> &bitSets);

protected:
    bool findInitialPair(const std::vector<std::vector<bool>> &bitSets, int &idx1, int &idx2, int &initialBestPosition);
    std::vector<bool> createMergedSequence(const std::vector<bool> &bitsetA, const std::vector<bool> &bitsetB,
                                           int positionB);
    void removeContainedBitsetsInMergedSeq(std::vector<bool> &mergedSeq,
                                           const std::vector<std::vector<bool>> &bitSets,
                                           std::vector<bool> &unusedFlags,
                                           std::unordered_map<int, std::vector<int>> &bitsetPositions);
    void mainFusionLoop(std::vector<bool> &mergedSeq, const std::vector<std::vector<bool>> &bitSets,
                        std::vector<bool> &unusedFlags, std::unordered_map<int, std::vector<int>> &bitsetPositions);
    std::vector<bool> mergeBitset(const std::vector<bool> &mergedSeq, const std::vector<bool> &newBitset, int position);
    void optimizeRedundancies(std::vector<bool> &mergedSeq, const std::vector<std::vector<bool>> &bitSets,
                              const std::vector<bool> &unusedFlags, std::unordered_map<int, std::vector<int>> &bitsetPositions);
    int computeMaxOverlap(const std::vector<bool> &mergedSeq, const std::vector<bool> &bitsetVec, int &bestPosition);
    std::vector<int> findOccurrences(const std::vector<bool> &mergedSeq, const std::vector<bool> &bitsetVec);
    bool allBitsetsContained(const std::vector<bool> &tempMerged, const std::vector<std::vector<bool>> &bitsetVecs,
                             const std::vector<bool> &unusedFlags);

private:

};

#endif // FUSEBYTE_H
