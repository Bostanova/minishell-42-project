#!/bin/sh

read commits_name
git status
git add .
git status
@echo Enter commits name:
git commit -m $commits_name
# git push origin ${USER}