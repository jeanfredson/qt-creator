/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "autotest_global.h"

#include <extensionsystem/iplugin.h>

#include <QMap>

namespace ProjectExplorer { class RunConfiguration; }

namespace Autotest {
namespace Internal {

class TestFrameworkManager;
class TestNavigationWidgetFactory;
class TestResultsPane;
struct TestSettings;
class TestSettingsPage;
enum class TestRunMode;

struct ChoicePair
{
    explicit ChoicePair(const QString &name = QString(), const QString &exe = QString())
        : displayName(name), executable(exe) {}
    bool matches(const ProjectExplorer::RunConfiguration *rc) const;

    QString displayName;
    QString executable;
};

class AutotestPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "AutoTest.json")

public:
    AutotestPlugin();
    ~AutotestPlugin() override;

    bool initialize(const QStringList &arguments, QString *errorString) override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

    static QSharedPointer<TestSettings> settings();
    static void updateMenuItemsEnabledState();
    static void cacheRunConfigChoice(const QString &buildTargetKey, const ChoicePair &choice);
    static ChoicePair cachedChoiceFor(const QString &buildTargetKey);
    static void clearChoiceCache();

private:
    bool checkLicense();
    void initializeMenuEntries();
    void onRunAllTriggered();
    void onRunSelectedTriggered();
    void onRunFileTriggered();
    void onRunUnderCursorTriggered(TestRunMode mode);
    QList<QObject *> createTestObjects() const override;
    const QSharedPointer<TestSettings> m_settings;
    TestFrameworkManager *m_frameworkManager = nullptr;
    TestSettingsPage *m_testSettingPage = nullptr;
    TestNavigationWidgetFactory *m_navigationWidgetFactory = nullptr;
    TestResultsPane *m_resultsPane = nullptr;
    QMap<QString, ChoicePair> m_runconfigCache;
};

} // namespace Internal
} // namespace Autotest
