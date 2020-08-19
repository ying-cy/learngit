set branchname=%~1

echo [exec script]: git reset --hard
git reset --hard
echo [exec script]: git version
git version
echo [exec script]: git clean -xdf -e .temp
git clean -xdf -e .temp
echo [exec script]: git remote prune origin
git remote prune origin
echo [exec script]: git branch
git branch
echo [exec script]: git gc --prune=now
git gc --prune=now
echo [exec script]: git remote prune origin
git remote prune origin
echo [exec script]: git fetch
git fetch
echo [exec script]: git reset --hard origin/%branchname%
git reset --hard origin/%branchname%
echo [exec script]: git reset --hard
git reset --hard
echo [exec script]: git pull -p
git pull -p

exit 0
