#include "gtest/gtest.h"
#include "AnyType.h"

TEST(AnyTypeTest, DefaultConstructor) {
    constexpr AnyType a;
    ASSERT_EQ(a.GetType(), AnyType::Type::None);
}

TEST(AnyTypeTest, ValueConstructionAndRetrieval) {
    AnyType a = 123;
    ASSERT_EQ(a.GetType(), AnyType::Type::Int);
    ASSERT_EQ(a.ToInt(), 123);

    AnyType b = 'x';
    ASSERT_EQ(b.GetType(), AnyType::Type::Char);
    ASSERT_EQ(b.ToChar(), 'x');

    AnyType c = 3.14;
    ASSERT_EQ(c.GetType(), AnyType::Type::Double);
    ASSERT_DOUBLE_EQ(c.ToDouble(), 3.14);

    AnyType d = true;
    ASSERT_EQ(d.GetType(), AnyType::Type::Bool);
    ASSERT_TRUE(d.ToBool());
}

TEST(AnyTypeTest, CopyConstructor) {
    const AnyType a = 42;
    const AnyType b = a;
    ASSERT_EQ(b.GetType(), AnyType::Type::Int);
    ASSERT_EQ(b.ToInt(), 42);
}

TEST(AnyTypeTest, MoveConstructor) {
    AnyType a = 99;
    const AnyType b = std::move(a);
    ASSERT_EQ(b.GetType(), AnyType::Type::Int);
    ASSERT_EQ(b.ToInt(), 99);
    ASSERT_EQ(a.GetType(), AnyType::Type::None);
}

TEST(AnyTypeTest, CopyAssignment) {
    const AnyType a = 100;
    AnyType b = 200.5;
    b = a;
    ASSERT_EQ(b.GetType(), AnyType::Type::Int);
    ASSERT_EQ(b.ToInt(), 100);
}

TEST(AnyTypeTest, MoveAssignment) {
    AnyType a = 55;
    AnyType b;
    b = std::move(a);
    ASSERT_EQ(b.GetType(), AnyType::Type::Int);
    ASSERT_EQ(b.ToInt(), 55);
    ASSERT_EQ(a.GetType(), AnyType::Type::None);
}

TEST(AnyTypeTest, ValueAssignment) {
    AnyType a;
    a = 7;
    ASSERT_EQ(a.GetType(), AnyType::Type::Int);
    ASSERT_EQ(a.ToInt(), 7);

    a = 12.5f;
    ASSERT_EQ(a.GetType(), AnyType::Type::Float);
    ASSERT_FLOAT_EQ(a.ToFloat(), 12.5f);
}

TEST(AnyTypeTest, Swap) {
    AnyType a = 10;
    AnyType b = 20.5;

    AnyType::Swap(a, b);

    ASSERT_EQ(a.GetType(), AnyType::Type::Double);
    ASSERT_DOUBLE_EQ(a.ToDouble(), 20.5);

    ASSERT_EQ(b.GetType(), AnyType::Type::Int);
    ASSERT_EQ(b.ToInt(), 10);
}

TEST(AnyTypeTest, Destroy) {
    AnyType a = 123;
    ASSERT_EQ(a.GetType(), AnyType::Type::Int);
    a.Destroy();
    ASSERT_EQ(a.GetType(), AnyType::Type::None);
}

TEST(AnyTypeTest, BadCast) {
    const AnyType a = 123;
    ASSERT_THROW(a.ToDouble(), std::bad_cast);
    ASSERT_THROW(a.ToChar(), std::bad_cast);
}

TEST(AnyTypeTest, SelfAssignment) {
    AnyType a = 42;
    a = a;
    ASSERT_EQ(a.GetType(), AnyType::Type::Int);
    ASSERT_EQ(a.ToInt(), 42);

    a = std::move(a);
    ASSERT_EQ(a.GetType(), AnyType::Type::Int);
    ASSERT_EQ(a.ToInt(), 42);
}

TEST(AnyTypeTest, TypeOverwriteOnValueAssignment) {
    AnyType a = 123;
    ASSERT_EQ(a.GetType(), AnyType::Type::Int);
    ASSERT_EQ(a.ToInt(), 123);

    a = 'z';
    ASSERT_EQ(a.GetType(), AnyType::Type::Char);
    ASSERT_EQ(a.ToChar(), 'z');
    ASSERT_THROW(a.ToInt(), std::bad_cast);
}