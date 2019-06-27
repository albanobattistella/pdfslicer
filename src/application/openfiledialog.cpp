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

#include "openfiledialog.hpp"
#include "pdffilter.hpp"
#include <glibmm/i18n.h>

namespace Slicer {

OpenFileDialog::OpenFileDialog(Gtk::Window& parent,
                               std::optional<std::string> folderPath)
    : Gtk::FileChooserDialog{parent,
                             _("Open document"),
                             Gtk::FILE_CHOOSER_ACTION_OPEN}
{
    add_button(_("Open"), Gtk::RESPONSE_ACCEPT);
    add_button(_("Cancel"), Gtk::RESPONSE_CANCEL);
    set_select_multiple(false);
    add_filter(pdfFilter());

    if (folderPath.has_value())
        set_current_folder(folderPath.value());
}

} // namespace Slicer
