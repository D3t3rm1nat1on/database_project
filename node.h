#pragma once

#include <string.h>
#include <memory.h>

#include "date.h"

enum class LogicalOperation {
    Or,
    And
};

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) = 0;

private:
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison cmp, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) override;

private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison cmp, const std::string& value);
    bool Evaluate(const Date& date, const std::string& event) override;

private:
    Comparison _cmp;
    std::string _event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation op, const std::shared_ptr<Node> left, const std::shared_ptr<Node> right);
    bool Evaluate(const Date& date, const std::string& event) override;

private:
    LogicalOperation _op;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const std::string& event) override;

private:
};
