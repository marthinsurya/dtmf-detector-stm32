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
git log --oneline (-n): list of push history (check n number of cinnut history)

## git branch
git switch (-c) <name> : switch to branch (-c create new bran)
git branch : list of branches, * marks the current one



## python
python --version
python xxxx.py : run the python file
write constant in capital so people know it never changes (eg. FS = 8000)
Tuple, F = (697, 770). A tuple can’t be modified, different from list [value]. Indexing F[1] works the same.


# GLOSSARY
DTMF -  Dual-Tone Multi-Frequency

