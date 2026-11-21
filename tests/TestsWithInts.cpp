//
// Created by EgrZver on 30.10.2026.
//

#include <gtest/gtest.h>
#include "../Array.h"

TEST(DynamicArrayTests_Ints, SimpleInsert) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    constexpr int check[] = {1, 2, 3, 4};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Ints, IndexedInsert) {

    Array<int> a(2);

    a.insert(1);
    a.insert(0, 2);
    a.insert(1, 3);
    a.insert(0, 4);

    constexpr int check[] = {4, 2, 3, 1};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Ints, Remove) {
    Array<int> a;

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    a.remove(1);
    a.remove(3);

    constexpr int check[] = {1, 3};

    EXPECT_EQ(2, a.size());
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Ints, Copy) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);

    Array<int> b = a;

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a[0], b[0]);
    EXPECT_EQ(a[1], b[1]);

    EXPECT_NE(&a[0], &b[0]);
    EXPECT_NE(&a[1], &b[1]);

    Array c(a);

    EXPECT_EQ(a.size(), c.size());
    EXPECT_EQ(a[0], c[0]);
    EXPECT_EQ(a[1], c[1]);

    EXPECT_NE(&a[0], &c[0]);
    EXPECT_NE(&a[1], &c[1]);
}

TEST(DynamicArrayTests_Ints, Move) {

    Array<int> a1(2);

    a1.insert(1);
    a1.insert(2);

    Array a2(a1);

    int* ptf1 = &a1[0];
    int* ptf2 = &a2[0];

    Array<int> b = std::move(a1);

    EXPECT_NE(a1.size(), b.size());
    EXPECT_EQ(2, b.size());
    EXPECT_EQ(1, b[0]);
    EXPECT_EQ(2, b[1]);
    EXPECT_EQ(ptf1, &b[0]);

    EXPECT_EQ(0, a1.size());

    Array c(std::move(a2));

    EXPECT_NE(a2.size(), c.size());
    EXPECT_EQ(2, c.size());
    EXPECT_EQ(1, c[0]);
    EXPECT_EQ(2, c[1]);
    EXPECT_EQ(ptf2, &c[0]);

    EXPECT_EQ(0, a2.size());
}

TEST(DynamicArrayTests_Ints, ReadIteration) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    Array<int>::Iterator it = a.iterator();
    int i = 1;

    while (it.hasNext()) {
        int v = it.get();
        EXPECT_EQ(i, v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Ints, WriteIteration) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    Array<int>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set(80085);
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(80085, a[2]);
}

TEST(DynamicArrayTests_Ints, ConstReadIteration) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    Array<int>::ConstIterator it = a.constIterator();
    int i = 1;

    while (it.hasNext()) {
        int v = it.get();
        EXPECT_EQ(i, v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Ints, ReadReverseIteration) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    Array<int>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        int v = it.get();
        EXPECT_EQ(4 - i, v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Ints, WriteReverseIteration) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    Array<int>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set(80085);
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(80085, a[1]);
}

TEST(DynamicArrayTests_Ints, ConstReadReverseIteration) {

    Array<int> a(2);

    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);

    Array<int>::ConstIterator it = a.reverseConstIterator();
    int i = 0;

    while (it.hasNext()) {
        int v = it.get();
        EXPECT_EQ(4 - i, v);
        ++i;
        it.next();
    }
}
