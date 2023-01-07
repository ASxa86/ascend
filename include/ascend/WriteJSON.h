#pragma once

#include <QJsonObject>
#include <ascend/export.hxx>

namespace ascend
{
	ASCEND_EXPORT auto WriteJSON(const QObject& x) -> QJsonObject;
}
