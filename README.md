# <img src="./misc/dvtm-repo.png" width="24"/> My build of [dvtm](https://github.com/martanne/dvtm) - dynamic virtual terminal manager

[dvtm](https://www.brain-dump.org/projects/dvtm/) brings the concept
of tiling window management, popularized by X11-window managers like
[dwm](https://dwm.suckless.org) to the console. As a console window
manager it tries to make it easy to work with multiple console based
programs.

![](./misc/screenshot.png)

## Usage
```sh
# Multiplexing only
dvtm

# Multiplexing with session management, with my build of abduco
# https://codeberg.org/unixchad/abduco
# https://github.com/gnuunixchad/abduco
abduco -c my-session
```

## Environment variables
```sh
export DVTM_EDITOR="/usr/bin/vim"    # copy mode editor
export DVTM_PAGER="/usr/bin/less -R" # scrollback history pager
```

## Statusbar
dvtm can read a named pipe and display it in the statusbar.
```sh
# run dvtm with status script
dvtm-status
```
Current modules in my [dvtm-status](./dvtm-status):
- Date
- Battery level with charging status
- Unread new emails count from isync/neomutt
- Login users count to be aware of SSH or TTY connections

## Patches applied

 - [pertag](./patches/dvtm-v0.15-52-g7bcf43f-pertag.diff)([Originally from](http://waxandwane.org/dvtm.html))

## Session management
My build of abduco([codeberg](https://codeberg.org/unixchad/abduco) or
[github](https://github.com/gnuunixchad/abduco))

## Dependencies
- ncurses

## Known Issues
### 1. neovim has every slow start/exit speed even with `--clean`
I have `nvim` aliased as `vim`, but when inside dvtm vim is preffered for better
performance:
```sh
if [ ! $UID -eq 0 ]; then
    command -v nvim >/dev/null \
        && [ -z "$DVTM" ] \
        && alias vim="nvim"
           vimdiff="nvim -d"
fi
```

### 2. dvtm doesn't support 24-bit color
I have created an autocmd to disable vim's 24-bit color inside dvtm:
```vim
augroup dvtm
    autocmd!
    autocmd BufEnter * if !empty(getenv('DVTM')) | setlocal notermguicolors | endif
augroup END
```

## License

dvtm reuses some code of dwm and is released under the same
[MIT/X11 license](https://raw.githubusercontent.com/martanne/dvtm/master/LICENSE).
The terminal emulation part is licensed under the ISC license.
