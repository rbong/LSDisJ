scriptencoding utf-8

" Utils

function! LsdjVersion() abort
  return get(g:, 'lsdj_version', '9.2.L')
endfunction

function! LsdisjDir() abort
  if !has_key(g:, 'lsdisj_src_dir')
    return expand('<script>:p:h:h')
  endif
  return g:lsdisj_src_dir
endfunction

function! LsdisjBuildDir() abort
  return LsdisjDir() .. '/build/' .. LsdjVersion()
endfunction

function! LsdisjStatsDir() abort
  return LsdisjDir() .. '/stats'
endfunction

function! LsdisjStatsFile() abort
  return LsdisjStatsDir() .. '/stats'
endfunction

function! LsdisjExcludedStatsFile() abort
  return LsdisjStatsDir() .. '/excluded-stats'
endfunction

function! IsLsdisjWin() abort
  return IsLsdisjStats() || IsLsdisjExcludedStats() || IsLsdisjBank() || IsLsdisjSym() || IsLsdisjInc()
endfunction

function! GotoLsdisjWin(win, open, fname, should_open = v:true) abort
  let l:open = a:open

  if has_key(g:, a:win) && win_gotoid(g:[a:win]) || expand('%:p') ==# ''
    let l:open = 'edit'
  endif

  if !a:should_open && has_key(g:, a:win) && win_getid() == g:[a:win]
    return
  endif

  if expand('%:p') != resolve(fnamemodify(a:fname, ':p'))
    silent! exec l:open .. ' ' .. a:fname
  endif

  let g:[a:win] = win_getid()
endfunction

" Stats windows

function! IsLsdisjStats() abort
  return get(g:, 'lsdisj_stats_win', -1) == win_getid()
endfunction

function! IsLsdisjExcludedStats() abort
  return get(g:, 'lsdisj_excluded_stats_win', -1) == win_getid()
endfunction

function! GotoLsdisjStats() abort
  call GotoLsdisjWin('lsdisj_stats_win', 'tabe', LsdisjStatsFile())
  tabm 0
  exec 'lcd ' .. LsdisjDir()
  set nowrap autoread
  105wincmd |
endfunction

function! GotoLsdisjExcludedStats() abort
  call GotoLsdisjStats()
  call GotoLsdisjWin('lsdisj_excluded_stats_win', 'belowright vs', LsdisjExcludedStatsFile())
  exec 'lcd ' .. LsdisjDir()
  set nowrap
  wincmd |
  104wincmd <
endfunction

function! GetLsdisjStatsLoc() abort
  " Check buffer
  if !IsLsdisjStats() && !IsLsdisjExcludedStats()
    return ['', '']
  endif

  " Init
  let l:pattern = '\v^call_\zs\x{2}_\x{4}'
  let l:y = 0

  " Search current line
  let l:match = match(getline('.'), l:pattern)
  if l:match >= 0
    let l:y = line('.')
    let l:x = l:match + 1
  endif

  " Search backwards
  if l:y <= 0
    let [l:y, l:x] = searchpos('\v^call_\zs\x{2}_\x{4}', 'Wnb')
  endif

  " Check location
  if l:y <= 0
    return ['', '']
  endif

  " Get location
  let l:line = getline(l:y)
  let l:address = l:line[l:x - 1:l:x + 5]

  return split(l:address, '_')
endfunction

" Bank window

function! IsLsdisjBank() abort
  return get(g:, 'lsdisj_bank_win', -1) == win_getid()
endfunction

function! GetLsdisjBankLoc() abort
  " Check buffer
  if !IsLsdisjBank()
    return ['', '']
  endif

  " Init
  let l:pattern = '\v\x{2}:\x{4}$'
  let l:y = 0

  " Search current line
  let l:match = match(getline('.'), l:pattern)
  if l:match >= 0
    let l:y = line('.')
    let l:x = l:match + 1
  endif

  " Search forward
  if l:y <= 0
    let [l:y, l:x] = searchpos(l:pattern, 'Wn')
  endif

  " Search backwards
  if l:y <= 0
    let [l:y, l:x] = searchpos(l:pattern, 'Wnb')
  endif

  " Check location
  if l:y <= 0
    return ['', '']
  endif

  " Get location
  let l:line = getline(l:y)
  let l:address = l:line[l:x - 1:]

  return split(l:address, ':')
endfunction

function! FindLsdisjBankLoc(bank, addr) abort
  call GotoLsdisjBank(a:bank)
  return search(a:bank .. ':' .. a:addr .. '$')
endfunction

function! GotoLsdisjBank(bank = '0', should_open = v:true) abort
  let l:bank = printf('%03s', a:bank)
  call GotoLsdisjStats()
  call GotoLsdisjWin('lsdisj_bank_win', 'tabe', LsdisjDir() .. '/build/' .. LsdjVersion() .. '/src/bank_' .. l:bank .. '.asm', a:should_open)
  set nowrap autoread
  exec 'lcd ' .. LsdisjDir()
  wincmd =
endfunction

" .sym window

function! IsLsdisjSym() abort
  return get(g:, 'lsdisj_sym_win', -1) == win_getid()
endfunction

function! GetLsdisjSymLoc() abort
  " Check buffer
  if !IsLsdisjSym()
    return ['', '']
  endif

  " Init
  let l:pattern = '\v^(;; )?\zs\x{2}:\x{4}'
  let l:y = 0

  " Search current line
  let l:match = match(getline('.'), l:pattern)
  if l:match >= 0
    let l:y = line('.')
    let l:x = l:match + 1
  endif

  " Search backwards
  if l:y <= 0
    let [l:y, l:x] = searchpos(l:pattern, 'Wnb')
  endif

  if l:y <= 0
    " Search forwards
    let [l:y, l:x] = searchpos(l:pattern, 'Wn')
  endif

  " Check location
  if l:y <= 0
    return ['', '']
  endif

  " Get location
  let l:line = getline(l:y)
  let l:address = l:line[l:x - 1:l:x + 5]

  return split(l:address, ':')
endfunction

function! FindLsdisjSymLoc(bank, addr, forwards = v:true) abort
  " Go to window
  call GotoLsdisjSym()

  " Init
  let l:line = 0
  let l:addr_num = str2nr(a:addr, 16)

  " Search forwards
  while l:addr_num >= 0
    let l:pattern = printf('^\v(;; )?%s:%04x', a:bank, l:addr_num)

    " Search current line
    let l:match = match(getline('.'), l:pattern)
    if l:match >= 0
      return l:match + 1
    endif

    " Search forwards/backwards
    let l:line = search(l:pattern, a:forwards ? '' : 'b')
    if l:line > 0
      return l:line
    endif

    let l:addr_num -= 1
  endwhile

  return 0
endfunction

function! GotoLsdisjSym() abort
  call GotoLsdisjBank('0', v:false)
  call GotoLsdisjWin('lsdisj_sym_win', 'belowright vs', LsdisjDir() .. '/src/lsdj-' .. LsdjVersion() .. '.sym')
  exec 'lcd ' .. LsdisjDir()
  set nowrap
  wincmd =
endfunction

function! GotoLsdisjBankOrSym() abort
  if IsLsdisjBank()
    return
  endif
  return GotoLsdisjSym()
endfunction

" .inc window

function! IsLsdisjInc() abort
  return get(g:, 'lsdisj_inc_win', -1) == win_getid()
endfunction

function! GotoLsdisjInc() abort
  call GotoLsdisjSym()
  call GotoLsdisjWin('lsdisj_inc_win', 'tabe', LsdisjDir() .. '/src/lsdj-' .. LsdjVersion() .. '.inc')
  exec 'lcd ' .. LsdisjDir()
  set nowrap
  wincmd =
endfunction

" Commands

function! Lsdisj() abort
  call GotoLsdisjStats()
  call GotoLsdisjExcludedStats()
  call GotoLsdisjBank('0', v:false)
  call GotoLsdisjSym()
  call GotoLsdisjInc()
  call win_gotoid(g:lsdisj_sym_win)
endfunction

function! LsdisjMake(args = ' ') abort
  let l:version = LsdjVersion()
  call GotoLsdisjBankOrSym()

  echo 'Building...'

  " Backup
  if !empty(finddir(LsdisjBuildDir()))
    call system('cp -r ' .. LsdisjBuildDir() .. '/src/* $(mktemp -d --suffix=-lsdj)')
  endif

  " Make
  exec '!make VERSION=' .. l:version .. ' ' .. a:args
endfunction

function! LsdisjStats() abort
  echo 'Installing...'
  call system('pip3 install -q ' .. LsdisjDir())
  call system('mkdir -p ' .. LsdisjStatsDir())
  exec '!python3 -m lsdisj.stats ' .. LsdisjBuildDir() .. '/src/bank_*.asm | grep -vf ' .. LsdisjExcludedStatsFile() .. ' | tee ' .. LsdisjStatsFile()
  call GotoLsdisjStats()
endfunction

function! LsdisjJump(forwards = v:true) abort
  " Get win type
  let l:is_from_bank = IsLsdisjBank()
  let l:is_from_stats = IsLsdisjStats() || IsLsdisjExcludedStats()
  let l:is_from_sym = IsLsdisjSym()

  " Jump to sym if not an LSDj win
  if !l:is_from_bank && !l:is_from_stats && !l:is_from_sym
    call GotoLsdisjSym()
    let l:is_from_sym = v:true
  endif

  " Save scroll
  let l:scroll = line('.') - winsaveview().topline

  " Get location
  if l:is_from_bank
    let [l:bank, l:addr] = GetLsdisjBankLoc()
  elseif l:is_from_sym
    let [l:bank, l:addr] = GetLsdisjSymLoc()
  else
    let [l:bank, l:addr] = GetLsdisjStatsLoc()
  endif

  " Check bank
  if empty(l:bank)
    return ['', '']
  endif

  " Find address in other file
  if l:is_from_bank
    let l:line = FindLsdisjSymLoc(l:bank, l:addr, a:forwards)
    " Restore
    if l:line <= 0
      call GotoLsdisjBank(l:bank)
    endif
  else
    let l:line = FindLsdisjBankLoc(l:bank, l:addr)
    " Restore
    if l:line <= 0
      if l:is_from_sym
        call GotoLsdisjSym()
      else
        call GotoLsdisjStats()
      endif
    endif
  endif

  " Check line
  if l:line <= 0
    return ['', '']
  endif

  " Align scroll
  if l:is_from_stats
    normal! zz
  else
    call winrestview({ 'topline': line('.') - l:scroll })
  endif

  " Set column
  if l:is_from_bank
    normal! 0
  else
    normal! 0^
  endif

  return [l:bank, l:addr]
endfunction

function! LsdisjComment() abort
  if IsLsdisjBank()
    let [l:bank, l:addr] = LsdisjJump(v:false)
  elseif IsLsdisjSym()
    let [l:bank, l:addr] = GetLsdisjSymLoc()
  else
    return
  endif

  if empty(l:bank)
    return
  endif

  call append('.', [';; ' .. l:bank .. ':' .. l:addr])
  normal! j
  startinsert!
endfunction

function! LsdisjLabel() abort
  if IsLsdisjBank()
    let [l:bank, l:addr] = LsdisjJump(v:false)
  elseif IsLsdisjSym()
    let [l:bank, l:addr] = GetLsdisjSymLoc()
  else
    return
  endif

  if empty(l:bank)
    return
  endif

  call append('.', ['', l:bank .. ':' .. l:addr .. ' '])
  normal! 2j
  startinsert!
endfunction

function! LsdisjYank() abort
  call GotoLsdisjBankOrSym()

  if IsLsdisjBank()
    let [l:bank, l:addr] = GetLsdisjBankLoc()
  else
    let [l:bank, l:addr] = GetLsdisjSymLoc()
  endif

  if empty(l:bank)
    return
  endif

  let @b = l:bank
  let @a = l:addr
  let @f = l:bank .. ':' .. l:addr
  let @c = 'call_' .. l:bank .. '_' .. l:addr
  let @d = 'data_' .. l:bank .. '_' .. l:addr
  let @" = @l
endfunction

command! -bar Lsdisj call Lsdisj()
command! -bar -nargs=* LsdisjBank call GotoLsdisjBank(<f-args>)
command! -bar -nargs=* LsdisjMake call LsdisjMake(<q-args>)
command! -bar LsdisjStats call LsdisjStats()
command! -bar LsdisjJump call LsdisjJump()
command! -bar LsdisjComment call LsdisjComment()
command! -bar LsdisjLabel call LsdisjLabel()
command! -bar LsdisjYank call LsdisjYank()

nno <leader>lb :<C-U>LsdisjBank<space>
nno <leader>lm :<C-U>LsdisjMake<space>
nno <silent> <leader>ls :<C-U>LsdisjStats<CR>
nno <silent> <leader>lj :<C-U>LsdisjJump<CR>
nno <silent> <leader>lc :<C-U>LsdisjComment<CR>
nno <silent> <leader>ll :<C-U>LsdisjLabel<CR>
nno <silent> <leader>ly :<C-U>LsdisjYank<CR>
