#include <stdexcept>

#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison cmp, const Date& date)
{
    _cmp = cmp;
    _date = date;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event)
{
    switch (_cmp) {
    case (Comparison::Less): {
        return date < _date;
    }
    case (Comparison::LessOrEqual): {
        return date <= _date;
    }
    case (Comparison::Greater): {
        return date > _date;
    }
    case (Comparison::GreaterOrEqual): {
        return date >= _date;
    }
    case (Comparison::Equal): {
        return date == _date;
    }
    case (Comparison::NotEqual): {
        return date != _date;
    }
    default: {
        throw std::runtime_error("Unknown Comparison");
    }
    }
}

EventComparisonNode::EventComparisonNode(const Comparison cmp, const std::string& value)
{
    _cmp = cmp;
    _event = value;
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event)
{
    switch (_cmp) {
    case (Comparison::Less):
        return event < _event;
    case (Comparison::LessOrEqual):
        return event <= _event;
    case (Comparison::Greater):
        return event > _event;
    case (Comparison::GreaterOrEqual):
        return event >= _event;
    case (Comparison::Equal):
        return event == _event;
    case (Comparison::NotEqual):
        return event != _event;
    default:
        throw std::runtime_error("Unknown Comparison");
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation op, const std::shared_ptr<Node> left, const std::shared_ptr<Node> right)
{
    _op = op;
    _left = left;
    _right = right;
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event)
{
    switch (_op) {
    case (LogicalOperation::Or):
        return _left->Evaluate(date, event) || _right->Evaluate(date, event);
    case (LogicalOperation::And):
        return _left->Evaluate(date, event) && _right->Evaluate(date, event);
    default:
        throw std::runtime_error("Unknown LogicalOperation");
    }
}

bool EmptyNode::Evaluate(const Date& date, const std::string& event)
{
    return false;
}
