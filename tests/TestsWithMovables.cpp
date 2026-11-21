//
// Created by EgrZver on 30.10.2026.
//

#include <gtest/gtest.h>
#include "../Array.h"
#include "TestClasses.h"

TEST(DynamicArrayTests_Movables, SimpleInsert) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    const SimpleMovableClass check[] = {{1, "d1"}, {2, "d2"}, {3, "d3"}, {4, "d4"}};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Movables, IndexedInsert) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert(0, {2, "d2"});
    a.insert(1, {3, "d3"});
    a.insert(0, {4, "d4"});

    const SimpleMovableClass check[] = {{4, "d4"}, {2, "d2"}, {3, "d3"}, {1, "d1"}};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Movables, Remove) {
    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    a.remove(1);
    a.remove(3);

    const SimpleMovableClass check[] = {
        {1, "d1"},
        {3, "d3"},
    };

    EXPECT_EQ(2, a.size());
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Movables, Copy) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});

    Array<SimpleMovableClass> b = a;

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

TEST(DynamicArrayTests_Movables, Move) {

    Array<SimpleMovableClass> a1(2);

    a1.insert({1, "d1"});
    a1.insert({2, "d2"});

    Array a2(a1);

    SimpleMovableClass* ptf1 = &a1[0];
    SimpleMovableClass* ptf2 = &a2[0];

    Array<SimpleMovableClass> b = std::move(a1);

    EXPECT_NE(a1.size(), b.size());
    EXPECT_EQ(2, b.size());
    EXPECT_EQ(SimpleMovableClass(1, "d1"), b[0]);
    EXPECT_EQ(SimpleMovableClass(2, "d2"), b[1]);
    EXPECT_EQ(ptf1, &b[0]);

    EXPECT_EQ(0, a1.size());

    Array c(std::move(a2));

    EXPECT_NE(a2.size(), c.size());
    EXPECT_EQ(2, c.size());
    EXPECT_EQ(SimpleMovableClass(1, "d1"), c[0]);
    EXPECT_EQ(SimpleMovableClass(2, "d2"), c[1]);
    EXPECT_EQ(ptf2, &c[0]);

    EXPECT_EQ(0, a2.size());
}

TEST(DynamicArrayTests_Movables, ReadIteration) {

    Array<SimpleMovableClass> a(2);

    const SimpleMovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    Array<SimpleMovableClass>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        SimpleMovableClass v = it.get();
        EXPECT_EQ(vals[i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Movables, WriteIteration) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    Array<SimpleMovableClass>::Iterator it = a.iterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set(SimpleMovableClass(69, "Nice"));
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(SimpleMovableClass(69, "Nice"), a[2]);
}

TEST(DynamicArrayTests_Movables, ConstReadIteration) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    const SimpleMovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };

    Array<SimpleMovableClass>::ConstIterator it = a.constIterator();
    int i = 0;

    while (it.hasNext()) {
        SimpleMovableClass v = it.get();
        EXPECT_EQ(vals[i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Movables, ReadReverseIteration) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    const SimpleMovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };
    Array<SimpleMovableClass>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        SimpleMovableClass v = it.get();
        EXPECT_EQ(vals[3 - i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Movables, WriteReverseIteration) {

    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});

    Array<SimpleMovableClass>::Iterator it = a.reverseIterator();
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set(SimpleMovableClass(69, "Nice"));
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ(SimpleMovableClass(69, "Nice"), a[1]);
}

TEST(DynamicArrayTests_Movables, ConstReadReverseIteration) {
    Array<SimpleMovableClass> a(2);

    a.insert({1, "d1"});
    a.insert({2, "d2"});
    a.insert({3, "d3"});
    a.insert({4, "d4"});
    const SimpleMovableClass vals[] = {
        {1, "d1"},
        {2, "d2"},
        {3, "d3"},
        {4, "d4"},
    };
    Array<SimpleMovableClass>::ConstIterator it = a.reverseConstIterator();
    int i = 0;

    while (it.hasNext()) {
        SimpleMovableClass v = it.get();
        EXPECT_EQ(vals[3 - i], v);
        ++i;
        it.next();
    }
}
