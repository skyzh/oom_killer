#!/bin/bash

set -e

(cd $KID && git diff android-goldfish-3.4) > patch.diff
(cd $KID && git archive --format=zip HEAD `git diff android-goldfish-3.4 HEAD --name-only`) > archive.zip
