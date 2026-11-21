//
// Created by EgrZver on 30.10.2026.
//

#include <gtest/gtest.h>
#include "../Array.h"

TEST(DynamicArrayTests_Strings, SimpleInsert) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert(std::string("abiba"));
    a.insert("abeba");
    a.insert("ababa");

    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Strings, IndexedInsert) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert(0, std::string("abiba"));
    a.insert(1, "abeba");
    a.insert(0, "ababa");

    const std::string check[] = {"ababa", "abiba", "abeba", "aboba"};

    EXPECT_EQ(4, a.size());
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Strings, Remove) {
    Array<std::string> a;

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    a.remove(1);
    a.remove(3);

    const std::string check[] = {"aboba", "abeba"};

    EXPECT_EQ(2, a.size());
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(check[i], a[i]);
    }
}

TEST(DynamicArrayTests_Strings, Copy) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");

    Array<std::string> b = a;

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

TEST(DynamicArrayTests_Strings, Move) {

    Array<std::string> a1(2);

    a1.insert("aboba");
    a1.insert("abiba");

    Array a2(a1);

    std::string* ptf1 = &a1[0];
    std::string* ptf2 = &a2[0];

    Array<std::string> b = std::move(a1);

    EXPECT_NE(a1.size(), b.size());
    EXPECT_EQ(2, b.size());
    EXPECT_EQ("aboba", b[0]);
    EXPECT_EQ("abiba", b[1]);
    EXPECT_EQ(ptf1, &b[0]);

    EXPECT_EQ(0, a1.size());

    Array c(std::move(a2));

    EXPECT_NE(a2.size(), c.size());
    EXPECT_EQ(2, c.size());
    EXPECT_EQ("aboba", c[0]);
    EXPECT_EQ("abiba", c[1]);
    EXPECT_EQ(ptf2, &c[0]);

    EXPECT_EQ(0, a2.size());
}

TEST(DynamicArrayTests_Strings, ReadIteration) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    Array<std::string>::Iterator it = a.iterator();
    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};
    int i = 0;

    while (it.hasNext()) {
        std::string v = it.get();
        EXPECT_EQ(check[i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Strings, WriteIteration) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    Array<std::string>::Iterator it = a.iterator();
    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set("abacus");
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ("abacus", a[2]);
}

TEST(DynamicArrayTests_Strings, ConstReadIteration) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    Array<std::string>::ConstIterator it = a.constIterator();
    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};
    int i = 0;

    while (it.hasNext()) {
        std::string v = it.get();
        EXPECT_EQ(check[i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Strings, ReadReverseIteration) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    Array<std::string>::Iterator it = a.reverseIterator();
    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};
    int i = 0;

    while (it.hasNext()) {
        std::string v = it.get();
        EXPECT_EQ(check[3 - i], v);
        ++i;
        it.next();
    }
}

TEST(DynamicArrayTests_Strings, WriteReverseIteration) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    Array<std::string>::Iterator it = a.reverseIterator();
    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};
    int i = 0;

    while (it.hasNext()) {
        if (i == 2) {
            it.set("abacus");
        }
        ++i;
        it.next();
    }

    EXPECT_EQ(4, a.size());
    EXPECT_EQ("abacus", a[1]);
}

TEST(DynamicArrayTests_Strings, ConstReadReverseIteration) {

    Array<std::string> a(2);

    a.insert("aboba");
    a.insert("abiba");
    a.insert("abeba");
    a.insert("ababa");

    Array<std::string>::ConstIterator it = a.reverseConstIterator();
    const std::string check[] = {"aboba", "abiba", "abeba", "ababa"};
    int i = 0;

    while (it.hasNext()) {
        std::string v = it.get();
        EXPECT_EQ(check[3 - i], v);
        ++i;
        it.next();
    }
}
