//
// Created by EgrZver on 30.10.2026.
//

//
// Created by EgrZver on 30.10.2026.
//

#include <gtest/gtest.h>
#include "../Array.h"
#include "TestClasses.h"

TEST(DynamicArrayTests_Unmovables, SimpleInsert) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    const UnmovableClass check[] = {{1, "d1"}, {2, "d2"}, {3, "d3"}, {4, "d4"}};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Unmovables, IndexedInsert) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert(0, {2, "d2"});
    a.insert(1, {3, "d3"});
    a.insert(0, {4, "d4"});

    const UnmovableClass check[] = {{4, "d4"}, {2, "d2"}, {3, "d3"}, {1, "d1"}};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Unmovables, Remove) {
    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    a.remove(1);
    a.remove(3);

    const UnmovableClass check[] = {
        {1, "d1"},
        {3, "d3"},
    };

    EXPECT_EQ(2, a.size());
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Unmovables, Copy) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});

    Array<UnmovableClass> b = a;

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

TEST(DynamicArrayTests_Unmovables, Move) {

    Array<UnmovableClass> a1(2);

    a1.insert({1, "d1"});
    a1.insert({2, "d2"});

    Array a2(a1);

    UnmovableClass* ptf1 = &a1[0];
    UnmovableClass* ptf2 = &a2[0];

    Array<UnmovableClass> b = std::move(a1);

    EXPECT_NE(a1.size(), b.size());
    EXPECT_EQ(2, b.size());
    EXPECT_EQ(UnmovableClass(1, "d1"), b[0]);
    EXPECT_EQ(UnmovableClass(2, "d2"), b[1]);
    EXPECT_EQ(ptf1, &b[0]);

    EXPECT_EQ(0, a1.size());

    Array c(std::move(a2));

    EXPECT_NE(a2.size(), c.size());
    EXPECT_EQ(2, c.size());
    EXPECT_EQ(UnmovableClass(1, "d1"), c[0]);
    EXPECT_EQ(UnmovableClass(2, "d2"), c[1]);
    EXPECT_EQ(ptf2, &c[0]);

    EXPECT_EQ(0, a2.size());
}

TEST(DynamicArrayTests_Unmovables, ReadIteration) {

    Array<UnmovableClass> a(2);

    const UnmovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    Array<UnmovableClass>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        UnmovableClass v = it.get();
        EXPECT_EQ(vals[i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Unmovables, WriteIteration) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    Array<UnmovableClass>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set(UnmovableClass(69, "Nice"));
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(UnmovableClass(69, "Nice"), a[2]);
}

TEST(DynamicArrayTests_Unmovables, ConstReadIteration) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    const UnmovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };

    Array<UnmovableClass>::ConstIterator it = a.constIterator();
    int i = 0;

    while (it.hasNext()) {
        UnmovableClass v = it.get();
        EXPECT_EQ(vals[i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Unmovables, ReadReverseIteration) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    const UnmovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };
    Array<UnmovableClass>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        UnmovableClass v = it.get();
        EXPECT_EQ(vals[3 - i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Unmovables, WriteReverseIteration) {

    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    Array<UnmovableClass>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set(UnmovableClass(69, "Nice"));
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(UnmovableClass(69, "Nice"), a[1]);
}

TEST(DynamicArrayTests_Unmovables, ConstReadReverseIteration) {
    Array<UnmovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});
    const UnmovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };
    Array<UnmovableClass>::ConstIterator it = a.reverseConstIterator();
    int i = 0;

    while (it.hasNext()) {
        UnmovableClass v = it.get();
        EXPECT_EQ(vals[3 - i], v);
        ++i;
        it.next();
    }
}
