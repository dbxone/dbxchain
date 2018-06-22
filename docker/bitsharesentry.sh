#!/bin/bash
DBXCHAIND="/usr/local/bin/witness_node"

# For blockchain download
VERSION=`cat /etc/bitshares/version`

## Supported Environmental Variables
#
#   * $DBXCHAIND_SEED_NODES
#   * $DBXCHAIND_RPC_ENDPOINT
#   * $DBXCHAIND_PLUGINS
#   * $DBXCHAIND_REPLAY
#   * $DBXCHAIND_RESYNC
#   * $DBXCHAIND_P2P_ENDPOINT
#   * $DBXCHAIND_WITNESS_ID
#   * $DBXCHAIND_PRIVATE_KEY
#   * $DBXCHAIND_TRACK_ACCOUNTS
#   * $DBXCHAIND_PARTIAL_OPERATIONS
#   * $DBXCHAIND_MAX_OPS_PER_ACCOUNT
#   * $DBXCHAIND_ES_NODE_URL
#   * $DBXCHAIND_TRUSTED_NODE
#

ARGS=""
# Translate environmental variables
if [[ ! -z "$DBXCHAIND_SEED_NODES" ]]; then
    for NODE in $DBXCHAIND_SEED_NODES ; do
        ARGS+=" --seed-node=$NODE"
    done
fi
if [[ ! -z "$DBXCHAIND_RPC_ENDPOINT" ]]; then
    ARGS+=" --rpc-endpoint=${DBXCHAIND_RPC_ENDPOINT}"
fi

if [[ ! -z "$DBXCHAIND_REPLAY" ]]; then
    ARGS+=" --replay-blockchain"
fi

if [[ ! -z "$DBXCHAIND_RESYNC" ]]; then
    ARGS+=" --resync-blockchain"
fi

if [[ ! -z "$DBXCHAIND_P2P_ENDPOINT" ]]; then
    ARGS+=" --p2p-endpoint=${DBXCHAIND_P2P_ENDPOINT}"
fi

if [[ ! -z "$DBXCHAIND_WITNESS_ID" ]]; then
    ARGS+=" --witness-id=$DBXCHAIND_WITNESS_ID"
fi

if [[ ! -z "$DBXCHAIND_PRIVATE_KEY" ]]; then
    ARGS+=" --private-key=$DBXCHAIND_PRIVATE_KEY"
fi

if [[ ! -z "$DBXCHAIND_TRACK_ACCOUNTS" ]]; then
    for ACCOUNT in $DBXCHAIND_TRACK_ACCOUNTS ; do
        ARGS+=" --track-account=$ACCOUNT"
    done
fi

if [[ ! -z "$DBXCHAIND_PARTIAL_OPERATIONS" ]]; then
    ARGS+=" --partial-operations=${DBXCHAIND_PARTIAL_OPERATIONS}"
fi

if [[ ! -z "$DBXCHAIND_MAX_OPS_PER_ACCOUNT" ]]; then
    ARGS+=" --max-ops-per-account=${DBXCHAIND_MAX_OPS_PER_ACCOUNT}"
fi

if [[ ! -z "$DBXCHAIND_ES_NODE_URL" ]]; then
    ARGS+=" --elasticsearch-node-url=${DBXCHAIND_ES_NODE_URL}"
fi

if [[ ! -z "$DBXCHAIND_TRUSTED_NODE" ]]; then
    ARGS+=" --trusted-node=${DBXCHAIND_TRUSTED_NODE}"
fi

## Link the bitshares config file into home
## This link has been created in Dockerfile, already
ln -f -s /etc/bitshares/config.ini /var/lib/bitshares

# Plugins need to be provided in a space-separated list, which
# makes it necessary to write it like this
if [[ ! -z "$DBXCHAIND_PLUGINS" ]]; then
   $DBXCHAIND --data-dir ${HOME} ${ARGS} ${DBXCHAIND_ARGS} --plugins "${DBXCHAIND_PLUGINS}"
else
   $DBXCHAIND --data-dir ${HOME} ${ARGS} ${BITSHARESD_ARGS}
fi
