// PDF Slicer
// Copyright (C) 2017-2018 Julián Unrrein

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SLICERVIEW_HPP
#define SLICERVIEW_HPP

#include <document.hpp>
#include "interactivepagewidget.hpp"
#include "taskrunner.hpp"
#include <queue>
#include <glibmm/dispatcher.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/flowbox.h>

namespace Slicer {

class View : public Gtk::EventBox {

public:
    View(TaskRunner& taskRunner,
         const std::function<void()>& onMouseWheelUp,
         const std::function<void()>& onMouseWheelDown);

    View(const View&) = delete;
    View& operator=(const View&) = delete;
    View(View&&) = delete;
    View& operator=(View&& src) = delete;

    ~View() override;

    void setDocument(Document& document, int targetWidgetSize);
    void changePageSize(int targetWidgetSize);
    void setShowFileNames(bool showFileNames);
    void selectPageRange(unsigned int first, unsigned int last);
    void selectAllPages();
    void selectOddPages();
    void selectEvenPages();
    void clearSelection();
    void invertSelection();
    void cancelRenderingTasks();

    unsigned int getSelectedChildIndex() const;
    std::vector<unsigned int> getSelectedChildrenIndexes() const;
    std::vector<unsigned int> getUnselectedChildrenIndexes() const;

    sigc::signal<void> selectedPagesChanged;

private:
    Gtk::FlowBox m_flowBox;
    std::list<std::shared_ptr<InteractivePageWidget>> m_pageWidgets;
    int m_pageWidgetSize = 0;
    bool m_showFileNames = false;
    Document* m_document = nullptr;
    std::vector<sigc::connection> m_documentConnections;
    TaskRunner& m_taskRunner;

    InteractivePageWidget* m_lastPageSelected = nullptr;

    std::shared_ptr<InteractivePageWidget> createPageWidget(const Glib::RefPtr<const Page>& page);

    void setupFlowbox();
    void setupSignalHandlers(const std::function<void()>& onMouseWheelUp,
                             const std::function<void()>& onMouseWheelDown);
    void onModelItemsChanged(guint position, guint removed, guint added);
    void onModelPagesRotated(const std::vector<unsigned int>& positions);
    void onModelPagesReordered(const std::vector<unsigned int>& positions);
    void onPageSelection(InteractivePageWidget* pageWidget);
    void onShiftSelection(InteractivePageWidget* pageWidget);
    void onPreviewRequested(const Glib::RefPtr<const Page>& page);
    void renderPage(const std::shared_ptr<InteractivePageWidget>& pageWidget);
    void clearState();

    static int sortFunction(Gtk::FlowBoxChild* a, Gtk::FlowBoxChild* b);
};
}

#endif // SLICERVIEW_HPP
