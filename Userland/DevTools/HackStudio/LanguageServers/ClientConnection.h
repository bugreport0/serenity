/*
 * Copyright (c) 2020, Itamar S. <itamar8910@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "../AutoCompleteResponse.h"
#include "CodeComprehensionEngine.h"
#include "FileDB.h"
#include <AK/HashMap.h>
#include <AK/LexicalPath.h>
#include <LibIPC/ClientConnection.h>

#include <Userland/DevTools/HackStudio/LanguageServers/LanguageClientEndpoint.h>
#include <Userland/DevTools/HackStudio/LanguageServers/LanguageServerEndpoint.h>

namespace LanguageServers {

class ClientConnection : public IPC::ClientConnection<LanguageClientEndpoint, LanguageServerEndpoint> {
public:
    explicit ClientConnection(NonnullOwnPtr<Core::Stream::LocalSocket>);
    ~ClientConnection() override;

    virtual void die() override;

protected:
    virtual void greet(String const&) override;
    virtual void file_opened(String const&, IPC::File const&) override;
    virtual void file_edit_insert_text(String const&, String const&, i32, i32) override;
    virtual void file_edit_remove_text(String const&, i32, i32, i32, i32) override;
    virtual void set_file_content(String const&, String const&) override;
    virtual void auto_complete_suggestions(GUI::AutocompleteProvider::ProjectLocation const&) override;
    virtual void find_declaration(GUI::AutocompleteProvider::ProjectLocation const&) override;
    virtual void get_parameters_hint(GUI::AutocompleteProvider::ProjectLocation const&) override;

    FileDB m_filedb;
    OwnPtr<CodeComprehensionEngine> m_autocomplete_engine;
};

}
