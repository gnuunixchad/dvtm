#!/usr/bin/sh
# @author nate zhou
# @since 2026
# update.sh - update files in dvtm repo

dotfiles="${HOME}/doc/unixchad/dotfiles"
dvtm="${HOME}/doc/unixchad/dvtm"

scripts="dvtm-status"

update_bin() {
    for script in $scripts; do
        cp ${dotfiles}/.local/bin/${script} ${dvtm}/
    done
}

update_bin
