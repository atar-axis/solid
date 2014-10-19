/*
    Copyright 2014 Alejandro Fiestas Olivares <afiestas@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#include "fdinhibitionjob.h"
#include "fdinhibition.h"

#include <QCoreApplication>
#include <QVariant>

#include <QDebug>
#include <unistd.h>

using namespace Solid;

FdInhibitionJob::FdInhibitionJob(Power::InhibitionTypes inhibitions, const QString &description, QObject* parent)
    : AbstractInhibitionJob(parent)
    , m_inhibition(new FdInhibition(inhibitions, description))
{
}

FdInhibitionJob::~FdInhibitionJob()
{
}

void FdInhibitionJob::doStart()
{
    connect(m_inhibition, &FdInhibition::stateChanged, this, &FdInhibitionJob::stateChanged);
    m_inhibition->start();
}

void FdInhibitionJob::stateChanged(Inhibition::State state)
{
    Q_UNUSED(state);

    disconnect(m_inhibition, 0, this, 0);
    emitResult();
}


Inhibition* FdInhibitionJob::inhibition()
{
    return new Inhibition(m_inhibition);
}