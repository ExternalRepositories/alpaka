#!/bin/bash

#
# Copyright 2017 Benjamin Worpitz
#
# This file is part of alpaka.
#
# alpaka is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# alpaka is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with alpaka.
# If not, see <http://www.gnu.org/licenses/>.
#

#-------------------------------------------------------------------------------
# e: exit as soon as one command returns a non-zero exit code.
set -e

ls "${HOME}"/cache

#-------------------------------------------------------------------------------
# Print the travis environment variables: http://docs.travis-ci.com/user/ci-environment/
echo "${TRAVIS_BRANCH}"
echo "${TRAVIS_BUILD_DIR}"
echo "${TRAVIS_BUILD_ID}"
echo "${TRAVIS_BUILD_NUMBER}"
echo "${TRAVIS_COMMIT}"
echo "${TRAVIS_COMMIT_RANGE}"
echo "${TRAVIS_JOB_ID}"
echo "${TRAVIS_JOB_NUMBER}"
echo "${TRAVIS_PULL_REQUEST}"
echo "${TRAVIS_SECURE_ENV_VARS}"
echo "${TRAVIS_REPO_SLUG}"
echo "${TRAVIS_OS_NAME}"
echo "${TRAVIS_TAG}"
