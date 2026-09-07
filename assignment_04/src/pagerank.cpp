#include "../include/pagerank.h"

#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;

PageRankResult pageRank(
    int numVertices,
    const CSR &csr,
    double damping,
    double tolerance,
    int maxIterations)
{
    PageRankResult result;

    result.iterations = 0;
    result.converged = false;

    if (numVertices <= 0)
        return result;

    const double initialRank =
        1.0 / numVertices;

    const double teleportation =
        (1.0 - damping) / numVertices;

    vector<double> currentRank(
        numVertices,
        initialRank);

    vector<double> nextRank(
        numVertices,
        0.0);

    for (int iteration = 1;
         iteration <= maxIterations;
         ++iteration)
    {
        fill(
            nextRank.begin(),
            nextRank.end(),
            teleportation);

        // Calculate total rank of dangling vertices.
        double danglingRank = 0.0;

        for (int vertex = 0;
             vertex < numVertices;
             ++vertex)
        {
            int outDegree =
                csr.rowPtr[vertex + 1] -
                csr.rowPtr[vertex];

            if (outDegree == 0)
            {
                danglingRank +=
                    currentRank[vertex];
            }
        }

        // Treat dangling vertices as linking to every vertex.
        double danglingContribution =
            damping *
            danglingRank /
            numVertices;

        for (int vertex = 0;
             vertex < numVertices;
             ++vertex)
        {
            nextRank[vertex] +=
                danglingContribution;
        }

        // Distribute rank through outgoing edges.
        for (int vertex = 0;
             vertex < numVertices;
             ++vertex)
        {
            int start =
                csr.rowPtr[vertex];

            int end =
                csr.rowPtr[vertex + 1];

            int outDegree =
                end - start;

            if (outDegree == 0)
                continue;

            double contribution =
                damping *
                currentRank[vertex] /
                outDegree;

            for (int index = start;
                 index < end;
                 ++index)
            {
                int neighbour =
                    csr.colIdx[index];

                nextRank[neighbour] +=
                    contribution;
            }
        }

        // Calculate convergence error.
        double totalChange = 0.0;

        for (int vertex = 0;
             vertex < numVertices;
             ++vertex)
        {
            totalChange +=
                abs(
                    nextRank[vertex] -
                    currentRank[vertex]);
        }

        // Simultaneous update.
        currentRank.swap(nextRank);

        result.iterations = iteration;

        if (totalChange <= tolerance)
        {
            result.converged = true;
            break;
        }
    }

    result.ranks = move(currentRank);

    return result;
}