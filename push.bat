@echo off
setlocal EnableDelayedExpansion

echo.
echo ============================
echo        Git Auto Push
echo ============================
echo.

git rev-parse --is-inside-work-tree >nul 2>&1
if errorlevel 1 (
    echo Error: This is not a Git repository.
    pause
    exit /b 1
)

set /p MESSAGE=Commit message: 

if "%MESSAGE%"=="" (
    set MESSAGE=Update
)

echo.
echo Staging files...
git add .

echo.
echo Committing...
git commit -m "%MESSAGE%"

echo.
echo Fetching remote...
git fetch origin

echo.
echo Rebasing...
git pull --rebase origin main

if errorlevel 1 (
    echo.
    echo ==========================================
    echo Rebase stopped because of a conflict.
    echo Resolve the conflict manually, then run:
    echo.
    echo     git rebase --continue
    echo.
    echo or
    echo.
    echo     git rebase --abort
    echo.
    echo ==========================================
    pause
    exit /b 1
)

echo.
echo Pushing...
git push origin main

if errorlevel 1 (
    echo.
    echo Push failed.
    pause
    exit /b 1
)

echo.
echo ============================
echo Push complete!
echo ============================

pause