#pragma once

#include <QJsonObject.h>
#include <ascend/export.hxx>

namespace ascend
{
	ASCEND_EXPORT auto ReadJSON(const QJsonObject& x) -> std::unique_ptr<QObject>;
	ASCEND_EXPORT auto ReadJSON(const QJsonObject& x, QObject& parent) -> QObject*;
}
