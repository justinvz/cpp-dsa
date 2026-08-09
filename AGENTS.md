# Repository Guidance

## Purpose And Collaboration

- This is a personal C++23 learning repository for LeetCode problems and custom data structures, with a long-term goal of quant-trading-level C++ skill.
- Default to hints, invariants, counterexamples, and code review. Do not implement a learning exercise unless the user explicitly asks you to write or edit it.
- Optimize guidance for correctness first, then complexity, ownership, integer safety, and measurable performance.

## Build

- Use the `default` CMake preset; it selects `/usr/bin/clang++-20`, Ninja, libc++, Debug mode, and `build/clang-20`.
- Configure with `cmake --preset default`; build everything with `cmake --build --preset default`.
- Build one problem with `cmake --build --preset default --target <source-basename>` and run `./build/clang-20/<source-basename>`.
- Problem target names come from the actual `problems/*.cpp` basename, which does not always match the title in the tracker.
- GoogleTest v1.17.0 is pinned with CMake `FetchContent`; the first configure requires network access. Problem targets exist only when `BUILD_TESTING=ON`.
- Ignore root-level `CMakeCache.txt`, `CMakeFiles/`, `Makefile`, and `compile_commands.json`; they are ignored in-source artifacts, not the canonical preset build.
- The preset's `-stdlib=libc++` is required by code using C++23 `<print>` and `<format>`.

## Repository Shape

- Each `problems/*.cpp` is a separate GoogleTest executable linked to `GTest::gtest_main`; keeping them separate avoids collisions between exercise-local types and functions.
- `containers/` contains active learning implementations, not production-compatible STL replacements. Inspect their current state before changing behavior.
- Keep exercise-specific `TreeNode`, `ListNode`, graph-node, and similar definitions local unless the user explicitly requests shared infrastructure.
- Older files may compile while containing unfinished implementations, commented checks, or weak happy-path tests; do not treat a successful full build as proof of correctness.

## Tests

- All problem and container tests are discovered by GoogleTest and registered with uniquely prefixed CTest names. Run everything with `ctest --preset default --output-on-failure`.
- Build one problem and run its tests with `cmake --build --preset default --target <source-basename>` followed by `ctest --preset default -R '^<source-basename>::' --output-on-failure`.
- `vector-tests` uses AddressSanitizer with Clang/GNU; its focused CTest regex is `'^vector-tests::'`.
- Test sources include GoogleTest and their required standard-library headers directly; use native `TEST`, `EXPECT_*`, and `ASSERT_*` APIs.
- Qualify custom types such as `jtd::vector` in tests to avoid accidentally testing `std::vector`.

## Problem Workflow

- Before graph or grid code, state the visited-state rule. Test a minimal case, a cycle or disconnected case, and uneven dimensions where applicable.
- Derive regression cases from every branch and precondition: empty, singleton, duplicates, monotonic input, integer extremes, skewed trees, and answers below the root.
- When reviewing a claimed solution, verify the implementation and tests rather than trusting its tracker status.

## Tracker

- When the user reports a LeetCode attempt, update `leetcode-tracker.md`: add the attempt, advance the through-date, and recalculate all Snapshot statistics.
- Record time as `HH:MM`; use `-` only when no time was recorded. Repeated attempts count as attempts but not unique problems.
- Record assistance, confidence, key insight, and revisit need honestly in the problem notes or revisit queue; do not infer these from elapsed time.
- Update `feedback.md` only when an attempt materially changes the current assessment, timeline, or next priorities.
- A source file existing does not by itself mean the problem was solved.

## Tooling

- `.clang-tidy` configures static-analysis checks, but clang-tidy is not wired into CMake or CI and may not be installed as a standalone executable.
- `.clang-tidy` requests `FormatStyle: file`, but the repository currently has no `.clang-format`; do not claim a repository formatter command exists.
