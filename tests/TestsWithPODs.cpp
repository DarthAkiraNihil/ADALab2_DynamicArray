//
// Created by EgrZver on 30.10.2026.
//

#include <gtest/gtest.h>
#include "../Array.h"

#include "TestClasses.h"

TEST(DynamicArrayTests_Pods, SimpleInsert) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        Podman real_pod = pods[i];
        Podman checked_pod = a[i];

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
    }
}

TEST(DynamicArrayTests_Pods, IndexedInsert) {

    Array<Podman> a;

    constexpr Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    a.insert(pods[0]);
    a.insert(0, pods[1]);
    a.insert(1, pods[2]);
    a.insert(0, pods[3]);

    constexpr int check[] = {3, 1, 2, 0};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        Podman real_pod = pods[check[i]];
        Podman checked_pod = a[i];

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
    }
}

TEST(DynamicArrayTests_Pods, Remove) {
    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    a.remove(1);
    a.remove(3);

    constexpr int check[] = {0, 2};

    EXPECT_EQ(2, a.size());
    for (int i = 0; i < 2; i++) {
        Podman real_pod = pods[check[i]];
        Podman checked_pod = a[i];

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
    }
}

TEST(DynamicArrayTests_Pods, Copy) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman> b = a;

    EXPECT_EQ(a.size(), b.size());
    for (int i = 0; i < 2; i++) {
        Podman a_pod = a[i];
        Podman b_pod = b[i];
        EXPECT_EQ(a_pod.podman_id, b_pod.podman_id);
        EXPECT_EQ(a_pod.pod_id, b_pod.pod_id);
        EXPECT_EQ(a_pod.cluster_id, b_pod.cluster_id);
        EXPECT_EQ(a_pod.is_running, b_pod.is_running);
        EXPECT_EQ(a_pod.children[0], b_pod.children[0]);
        EXPECT_EQ(a_pod.children[1], b_pod.children[1]);
        EXPECT_NE(&a_pod, &b_pod);
    }

    Array c(a);

    EXPECT_EQ(a.size(), c.size());
    for (int i = 0; i < 2; i++) {
        Podman a_pod = a[i];
        Podman c_pod = c[i];
        EXPECT_EQ(a_pod.podman_id, c_pod.podman_id);
        EXPECT_EQ(a_pod.pod_id, c_pod.pod_id);
        EXPECT_EQ(a_pod.cluster_id, c_pod.cluster_id);
        EXPECT_EQ(a_pod.is_running, c_pod.is_running);
        EXPECT_EQ(a_pod.children[0], c_pod.children[0]);
        EXPECT_EQ(a_pod.children[1], c_pod.children[1]);
        EXPECT_NE(&a_pod, &c_pod);
    }
}

TEST(DynamicArrayTests_Pods, Move) {

    Array<Podman> a1(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a1.insert(pod);
    }

    Array a2(a1);

    Podman* ptf1 = &a1[0];
    Podman* ptf2 = &a2[0];

    Array<Podman> b = std::move(a1);

    EXPECT_NE(a1.size(), b.size());
    EXPECT_EQ(2, b.size());

    for (int i = 0; i < 2; i++) {
        Podman o_pod = pods[i];
        Podman b_pod = b[i];
        EXPECT_EQ(o_pod.podman_id, b_pod.podman_id);
        EXPECT_EQ(o_pod.pod_id, b_pod.pod_id);
        EXPECT_EQ(o_pod.cluster_id, b_pod.cluster_id);
        EXPECT_EQ(o_pod.is_running, b_pod.is_running);
        EXPECT_EQ(o_pod.children[0], b_pod.children[0]);
        EXPECT_EQ(o_pod.children[1], b_pod.children[1]);
        EXPECT_NE(&o_pod, &b_pod);
    }

    EXPECT_EQ(ptf1, &b[0]);

    EXPECT_EQ(0, a1.size());

    Array c(std::move(a2));

    EXPECT_NE(a2.size(), c.size());
    EXPECT_EQ(2, c.size());
    for (int i = 0; i < 2; i++) {
        Podman o_pod = pods[i];
        Podman c_pod = c[i];
        EXPECT_EQ(o_pod.podman_id, c_pod.podman_id);
        EXPECT_EQ(o_pod.pod_id, c_pod.pod_id);
        EXPECT_EQ(o_pod.cluster_id, c_pod.cluster_id);
        EXPECT_EQ(o_pod.is_running, c_pod.is_running);
        EXPECT_EQ(o_pod.children[0], c_pod.children[0]);
        EXPECT_EQ(o_pod.children[1], c_pod.children[1]);
        EXPECT_NE(&o_pod, &c_pod);
    }

    EXPECT_EQ(ptf2, &c[0]);

    EXPECT_EQ(0, a2.size());
}

TEST(DynamicArrayTests_Pods, ReadIteration) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        Podman real_pod = pods[i];
        Podman checked_pod = it.get();

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Pods, WriteIteration) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set({.podman_id = 69, .pod_id = 420, .cluster_id = 80085, .is_running = false, .children = {-1, -1}});
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    const Podman edited = a[2];

    EXPECT_EQ(69, edited.podman_id);
    EXPECT_EQ(420, edited.pod_id);
    EXPECT_EQ(80085, edited.cluster_id);
    EXPECT_EQ(false, edited.is_running);
    EXPECT_EQ(-1, edited.children[0]);
    EXPECT_EQ(-1, edited.children[1]);
}

TEST(DynamicArrayTests_Pods, ConstReadIteration) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman>::ConstIterator it = a.constIterator();
    int i = 0;

    while (it.hasNext()) {
        Podman real_pod = pods[i];
        Podman checked_pod = it.get();

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Pods, ReadReverseIteration) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        Podman real_pod = pods[3 - i];
        Podman checked_pod = it.get();

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Pods, WriteReverseIteration) {

    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set({.podman_id = 69, .pod_id = 420, .cluster_id = 80085, .is_running = false, .children = {-1, -1}});
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    const Podman edited = a[1];

    EXPECT_EQ(69, edited.podman_id);
    EXPECT_EQ(420, edited.pod_id);
    EXPECT_EQ(80085, edited.cluster_id);
    EXPECT_EQ(false, edited.is_running);
    EXPECT_EQ(-1, edited.children[0]);
    EXPECT_EQ(-1, edited.children[1]);
}

TEST(DynamicArrayTests_Pods, ConstReadReverseIteration) {
    Array<Podman> a(2);

    Podman pods[] = {
        {.podman_id = 0, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {1, 2}},
        {.podman_id = 1, .pod_id = 0, .cluster_id = 0, .is_running = true, .children = {-1, -1}},
        {.podman_id = 2, .pod_id = 0, .cluster_id = 0, .is_running = false, .children = {-1, -1}},
        {.podman_id = 0, .pod_id = 0, .cluster_id = 1, .is_running = true, .children = {-1, -1}},
    };

    for (const auto& pod: pods) {
        a.insert(pod);
    }

    Array<Podman>::ConstIterator it = a.reverseConstIterator();
    int i = 0;

    while (it.hasNext()) {
        Podman real_pod = pods[3 - i];
        Podman checked_pod = it.get();

        EXPECT_EQ(real_pod.podman_id, checked_pod.podman_id);
        EXPECT_EQ(real_pod.pod_id, checked_pod.pod_id);
        EXPECT_EQ(real_pod.cluster_id, checked_pod.cluster_id);
        EXPECT_EQ(real_pod.is_running, checked_pod.is_running);
        EXPECT_EQ(real_pod.children[0], checked_pod.children[0]);
        EXPECT_EQ(real_pod.children[1], checked_pod.children[1]);
        ++i;
        it.next();
    }
}
