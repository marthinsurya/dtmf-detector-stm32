# GIT notes
git status : check status of the files untracked etc
## setup folder
git init : initiate the folder
create .gitignore file : contains files to ignore in git command

## staging file (still offline - hidden folder)
git add <file1> <file2>: add a file into git
git commit -m "message" -m "description" : stage the file

git commit -a -m "msg" : combining add and commit action (only to already traced files, new files will be skip)
git commit --amend -m "msg" : change rewrite last commit (before push)

## link to remote
git remote add <origin> <link> : link to the github nicknamed "origin"

## push to remote
git push (-u <origin> <main/branch-name>) : push to remote (use origin main only for first push)

## list history
git log --oneline (-n): list of push history (check n number of xommir history)
git log --all --name-only --pretty=format: | sort -u : check file name in the file

## git branch
git switch (-c) <name> : switch to branch (-c create new bran)
git branch : list of branches, * marks the current one
git stash : shelves the edits, then you switch branch, then git stash pop brings them back onto the branch you want. This is best when you’re on the wrong branch with uncommited changes.
git branch -vv
git merge main : merge branch to main

## misc
git rm <file> : remove file


## python
python --version
python xxxx.py : run the python file
write constant in capital so people know it never changes (eg. FS = 8000)
Tuple, F = (697, 770). A tuple can’t be modified, different from list [value]. Indexing F[1] works the same.
python -c "import matplotlib; print(matplotlib.__version__)" : check if install and import correctly

## git check
git log --oneline : list of push history
git ls-tree --name-only <main/branch>
git log origin/main..main --oneline : shows commits that are on local main but not yet on GitHub’s main. Empty output means they’re in sync.
git diff main <branch> --stat :difference between main-branch

# GLOSSARY
DTMF -  Dual-Tone Multi-Frequency

