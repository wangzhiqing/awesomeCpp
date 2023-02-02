# get git hash
macro(get_git_hash _git_hash)
    set(ENV{GIT_DIR} ${PROJECT_SOURCE_DIR}/.git)
    execute_process(
        COMMAND git rev-parse --short HEAD
        OUTPUT_VARIABLE ${_git_hash}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_VARIABLE GET_GIT_VERSION_FAILED
    )
    #IF(GET_GIT_VERSION_FAILED)
    #    MESSAGE(FATAL_ERROR ${GET_GIT_VERSION_FAILED})
    #ELSE(GET_GIT_VERSION_FAILED)
    #    MESSAGE("-- Current Git Commit ID: ${_git_hash}")
    #    add_definitions(-DDEFINED_GIT_CID)
    #ENDIF(GET_GIT_VERSION_FAILED)
endmacro()

# get git branch
macro(get_git_branch _git_branch)
    set(ENV{GIT_DIR} ${PROJECT_SOURCE_DIR}/.git)
    execute_process(COMMAND git symbolic-ref --short -q HEAD
        #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE ${_git_branch}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endmacro()

# 生成版本描述字符串类似 TAG-X-gHASH
macro(get_git_tag_hash _git_tag_hash)
    set(ENV{GIT_DIR} ${PROJECT_SOURCE_DIR}/.git)
    execute_process(COMMAND git describe --abbrev=6 --dirty --always --tags
        # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE  ${_git_tag_hash}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endmacro()

# 获取最新 commit 日期，YYYY-MM-DD
macro(get_git_date_time _git_date_time)
    set(ENV{GIT_DIR} ${PROJECT_SOURCE_DIR}/.git)
    execute_process(COMMAND git log -1 --format=%cd --date=short
        # WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE  ${_git_date_time}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endmacro()
