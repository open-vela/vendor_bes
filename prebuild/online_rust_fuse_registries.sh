#!/bin/bash
# File: online_rust_fuse_registries.sh

# --- Help Function ---
show_help() {
    echo "Usage: $(basename "$0") [PROJECT_PATH]"
    echo
    echo "Goal: Fuses multiple Cargo lockfiles into a single local offline registry."
    echo
    echo "Arguments:"
    echo "  PROJECT_PATH    Path to the project root containing your Rust apps."
    echo
    echo "Options:"
    echo "  -h, --help      Display this help message and exit."
    echo
    echo "Requirements:"
    echo "  Requires 'cargo-local-registry' (cargo install cargo-local-registry)."
}

# --- Argument Parsing ---
if [[ "$1" == "-h" || "$1" == "--help" || -z "$1" ]]; then
    show_help
    exit 0
fi

# 1. Configuration
FINAL_REGISTRY="rust_offline_registry"
TEMP_DIR="temp_sync"
PROJECT=$1
rm -rf "$FINAL_REGISTRY" "$TEMP_DIR"
mkdir -p "$FINAL_REGISTRY/index"

# 2. List all your target Lockfiles
LOCKFILES=(
    "${HOME}/.rustup/toolchains/1.91.0-x86_64-unknown-linux-gnu/lib/rustlib/src/rust/library/Cargo.lock"
    "${PROJECT}/rtos/apps/examples/rust/hello/Cargo.lock"
    "${PROJECT}/rtos/apps/examples/rust/iperf/Cargo.lock"
)

echo "Starting Registry Fusion..."

for LOCK in "${LOCKFILES[@]}"; do
    if [ ! -f "$LOCK" ]; then echo "Skip: $LOCK"; continue; fi
    echo "--- Processing: $LOCK ---"

    # Sync this specific lockfile to a temporary folder
    rm -rf "$TEMP_DIR"
    cargo local-registry --sync "$LOCK" "$TEMP_DIR"

    # A. Copy all .crate files (Duplicates will just overwrite with same content)
    cp "$TEMP_DIR"/*.crate "$FINAL_REGISTRY/" 2>/dev/null

    # B. Fuse the Index (The magic part)
    # We walk the temp index and append lines to the master index
    cd "$TEMP_DIR/index"
    find . -type f | while read -r idx_file; do
        mkdir -p "../../$FINAL_REGISTRY/index/$(dirname "$idx_file")"
        # Append lines and remove duplicates to keep the index clean
        cat "$idx_file" >> "../../$FINAL_REGISTRY/index/$idx_file"
        sort -u "../../$FINAL_REGISTRY/index/$idx_file" -o "../../$FINAL_REGISTRY/index/$idx_file"
    done
    cd ../..
done

rm -rf "$TEMP_DIR"
echo "------------------------------------------------"
echo "Success! Universal Registry created at: $FINAL_REGISTRY"
echo "Contains versions found in all provided lockfiles."
