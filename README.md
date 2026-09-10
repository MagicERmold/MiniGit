# MiniGit

## About the project

MiniGit is a lightweight local version control system implemented from scratch in C++, designed to explore the internal concepts behind Git such as content-addressable storage, staging areas, commits, snapshots and history traversal.
MiniGit recreates the core workflow of Git — staging files, creating commits, browsing history and restoring previous snapshots — without relying on Git internally.

## Why MiniGit?

The goal of this project is to understand how a version control system works internally by implementing its core concepts from scratch.

Instead of treating Git as a black box, MiniGit explores concepts such as:
- content-addressable storage
- file hashing
- staging areas
- immutable snapshots
- commit history
- repository state management


## Features

### Core
- [ ] Initialize a MiniGit repository
- [ ] Add files to the staging area
- [ ] Show repository status
- [ ] Create commits
- [ ] View commit history

### Extended
- [ ] Inspect a specific commit
- [ ] Restore a previous commit
- [ ] Compare file versions
- [ ] Add all modified files

### Future
- [ ] Branch creation
- [ ] Branch switching

// Commenti per me stesso
## Obiettivo
Deve funzionare questo:
minigit init
minigit add <file>
minigit status
minigit commit -m "..."
minigit log


Può fare questo:
minigit checkout <commit>
minigit show <commit>
minigit diff
minigit add .


Extra:
minigit branch
minigit switch