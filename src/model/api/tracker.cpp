/*
Logic for diver tracker
*/

#include "tracker.h"

using Segment = DecoModel::Segment;

void DecoModel::Tracker::construct_profile(std::vector<Segment*> segments) {
    int n, sample;
    int seg_prof;

    for (Segment* segment: segments) {
        n = static_cast<int> (segment->time / dt);

        for (sample = 0; sample < n; sample++) {
            seg_prof = segment->start_depth + segment->rate * dt * sample;
            depth_profile.push_back(seg_prof);
        }


    }

}