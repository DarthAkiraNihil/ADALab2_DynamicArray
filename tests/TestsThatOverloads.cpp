//
// Created by EgrZver on 31.10.2026.
//

#include <gtest/gtest.h>
#include "../Array.h"
#include "TestClasses.h"

TEST(DynamicArrayTests_OVERDRIVE, IntOverdrive) {

    Array<int> a;

    for (int i = 0; i < 42080085; i++) {
        a.insert(i);
        a.insert(i * 2);
        a.insert(i * 4);
        a.insert(i * 8);
    }

    for (int i = 0; i < 42080085; i++) {
        a.remove(a.size() - 1);
    }

    // if we go here, all is ok!
}

TEST(DynamicArrayTests_OVERDRIVE, StringOverdrive) {

    Array<std::string> a;

    for (int i = 0; i < 80085; i++) {
        a.insert("abboba");
        a.insert("abiba");
        a.insert("abebaabababab");
        a.insert("jarvet jaihin jaa!");
    }

    for (int i = 0; i < 80085; i++) {
        a.remove(a.size() - 1);
    }

    // if we go here, all is ok!
}

TEST(DynamicArrayTests_OVERDRIVE, PodOverdrive) {

    Array<Podman> a;

    for (int i = 0; i < 420; i++) {
        a.insert({.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}});
        a.insert({.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}});
        a.insert({.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}});
        a.insert({.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}});
    }

    for (int i = 0; i < 420; i++) {
        a.remove(a.size() - 1);
    }

    // if we go here, all is ok!
}

TEST(DynamicArrayTests_OVERDRIVE, MovableOverdrive) {

    Array<SimpleMovableClass> a;

    for (int i = 0; i < 69; i++) {
        a.insert(SimpleMovableClass(1, "aboba"));
        a.insert(SimpleMovableClass(2, "abiba"));
        a.insert(SimpleMovableClass(4, "abeba"));
        a.insert(SimpleMovableClass(8, "ababa"));
    }

    for (int i = 0; i < 69; i++) {
        a.remove(a.size() - 1);
    }

    // if we go here, all is ok!
}

TEST(DynamicArrayTests_OVERDRIVE, UnmovableOverdrive) {

    Array<UnmovableClass> a;

    for (int i = 0; i < 69; i++) {
        a.insert(UnmovableClass(1, "aboba"));
        a.insert(UnmovableClass(2, "abeba"));
        a.insert(UnmovableClass(4, "ababa"));
        a.insert(UnmovableClass(8, "abiba"));
    }

    for (int i = 0; i < 69; i++) {
        a.remove(a.size() - 1);
    }

    // if we go here, all is ok!
}
