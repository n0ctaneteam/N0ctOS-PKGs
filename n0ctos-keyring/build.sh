#!/bin/env bash

contributors_dir="./contributors"
keyring_dir="."
gpg_tmp="$(mktemp -d)"

cleanup() { rm -rf "$gpg_tmp"; }
trap cleanup EXIT

chmod 700 "$gpg_tmp"

keyids=()

for dir in "$contributors_dir"/*/; do
    name="$(basename "$dir")"
    keyfile="$dir/pubkey.asc"
    tomlfile="$dir/info.toml"

    if [[ ! -f "$keyfile" ]]; then
        echo "[WARN] no pubkey.asc in $name/, skipping"
        continue
    fi

    echo "--> importing: $name"
    GNUPGHOME="$gpg_tmp" gpg --import "$keyfile" 2>/dev/null

    if [[ -f "$tomlfile" ]]; then
        keyid=$(grep 'keyid' "$tomlfile" | sed 's/.*= *"\(.*\)"/\1/')
        keyids+=("$keyid")
        echo "    key: $keyid"
    else
        echo "[WARN] no info.toml in $name/, skipping trusted entry"
    fi
done

if [[ ${#keyids[@]} -eq 0 ]]; then
    error "no contributor keys found. add at least one contributor."
    return 1
fi

echo "--> exporting bundle -> keyring/n0ctos.gpg"
GNUPGHOME="$gpg_tmp" gpg --export "${keyids[@]}" > "$keyring_dir/n0ctos.gpg"

echo "--> writing keyring/n0ctos-trusted"
printf '%s:6:\n' "${keyids[@]}" > "$keyring_dir/n0ctos-trusted"

if [[ ! -f "$keyring_dir/n0ctos-revoked" ]]; then
    touch "$keyring_dir/n0ctos-revoked"
fi

echo "--> keyring ready (${#keyids[@]} keys)"