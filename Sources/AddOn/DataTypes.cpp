#include	"DataTypes.hpp"

namespace ReaderData
{

QTY operator+ (const QTY& lhs, const QTY& rhs)
{
    QTY out;
    out.qtyraw = lhs.qtyraw + rhs.qtyraw;
    FormatString stringformat = lhs.stringformat;
    if (stringformat.isEmpty) stringformat = rhs.stringformat;
    double lhsqtyrounded = FormatStringFunc::NumRound (lhs.qtyraw, lhs.stringformat);
    double rhsqtyrounded = FormatStringFunc::NumRound (rhs.qtyraw, rhs.stringformat);
    out.qtyrounded = lhsqtyrounded + rhsqtyrounded;
    return out;
}
QTY operator+= (const QTY& lhs, const QTY& rhs)
{
    return lhs + rhs;
}
}
