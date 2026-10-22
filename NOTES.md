# GIT notes
git status : check status of the files untracked etc
## setup folder
git init : initiate the folder
.gitignore file : contains files to ignore in git command

## staging file (still offline - hidden folder)
git add <filename> : add a file into git
git commit -m "message" -m "description" : stage the file

git commit -a -m "msg" : combining add and commit action (only to already traced files, new files will be skip)

## link to remote
git remote add origin <link-github> : link to the github

## push to remote
git push (-u origin main) : push to remote (use origin main only for first push)

## git check
git log --oneline : list of push history
git ls-tree --name-only <main/branch>

# GLOSSARY
DTMF -  Dual-Tone Multi-Frequency

