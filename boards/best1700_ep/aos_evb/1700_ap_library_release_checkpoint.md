# best1700_ep AP Library Release Branch Checkpoint

## Branch

- `feature/1700-ap-library`

## Current State

This branch now contains the validated library-mode build logic needed to make
`best1700_ep` AP consume the published prebuilt BSP archives from:

- `boards/best1700_ep/aos_evb/configs/ap/`

The following logic has been brought onto this branch from the validated dev
flow:

- `boards/CMakeLists.txt`
- `boards/common/CMakeLists.txt`
- `boards/common/Kconfig`
- `boards/common/src/CMakeLists.txt`
- `chips/bes/CMakeLists.txt`
- `boards/best1700_ep/aos_evb/CMakeLists.txt`
- `boards/best1700_ep/aos_evb/cmake/Toolchain.cmake`
- `boards/best1700_ep/aos_evb/src/CMakeLists.txt`
- `boards/best1700_ep/aos_evb/configs/ap/CMakeLists.txt`
- `boards/best1700_ep/aos_evb/Kconfig`
- `boards/best1700_ep/aos_evb/configs/ap/defconfig`

`configs/ap/defconfig` now enables:

- `CONFIG_BES1700_AP_LIBRARY_MODE=y`

## What Has Been Validated

### 1. Dedicated validation config

A temporary `ap_lib` validation config was created and used on the dev branch.
That library-mode path built successfully end to end.

That confirmed the following build model is sound:

- `libbesboard_ap.a`
- `libbeschip_ap.a`
- `libnx_bestbsp_ap.a`
- no overlapping board/chip/common source ownership in the same link

### 2. Standard customer-facing `configs/ap` shape

On this release branch, the standard `configs/ap` flow now enters library mode
correctly.

Observed during clean configure:

- `libbesboard_ap.a` is detected
- `libbeschip_ap.a` is detected
- `libnx_bestbsp_ap.a` is selected as the prebuilt BSP archive
- the branch no longer depends on rebuilding the external BES SDK BSP path for
  AP library mode

## Current Blocker

The remaining blocker is not the library-mode build logic.
It is release payload completeness.

The standard `configs/ap` customer-facing build still needs runtime asset files
that are referenced by the AP defconfig and board rules but are not yet present
on this branch.

The first confirmed missing file is:

- `boards/best1700_ep/aos_evb/src/etc/txtable.txt`

The AP rules also reference these runtime assets when their configs are enabled:

- `boards/best1700_ep/aos_evb/src/etc/media/graph.conf`
- `boards/best1700_ep/aos_evb/src/etc/media/criteria.txt`
- `boards/best1700_ep/aos_evb/src/etc/media/settings.pfw`
- `boards/best1700_ep/aos_evb/src/etc/media/media_focus.conf`
- `boards/best1700_ep/aos_evb/src/etc/zoneinfo/*`

## Next Step

Continue adding only the missing customer-needed runtime files from the validated
source branch into `feature/1700-ap-library`, then rerun the standard
`configs/ap` build until the customer-facing release shape passes end to end.

## Update

The standard customer-facing `configs/ap` release shape now completes successfully on `feature/1700-ap-library` through the normal AP build flow (using `./build.sh ... configs/ap --cmake -b cmake_out/aos_evb_ap ...`).

This means the release branch now contains:

- the validated library-mode build logic
- the required runtime asset payload under `src/etc/`
- the required chip header payload under `chips/bes/include/`
- the required post-build tool `framework/services/tools/fill_sec_base.pl`

Current remaining work is no longer build bring-up. The next step is to clean up the branch payload and prepare the final customer submission commit sequence.
