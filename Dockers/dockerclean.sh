#!/usr/bin/env bash

# ===============================================
# Docker Total Cleanup Script
# ===============================================
# This will remove ALL Docker containers, images,
# volumes, and networks. Use with caution.

set -e

echo "🚀 Starting Docker full cleanup..."


# Remove all containers
echo -e "\n📦 Removing all Docker containers..."
sudo docker ps -aq | xargs -r sudo docker rm -f

# Remove all images
echo -e "\n🖼 Removing all Docker images..."
sudo docker images -aq | xargs -r sudo docker rmi -f

# Remove all volumes
echo -e "\n📁 Removing all Docker volumes..."
sudo docker volume ls -q | xargs -r sudo docker volume rm -f

# Remove all networks
echo -e "\n🌐 Removing all Docker networks (unused)..."
sudo docker network ls -q | xargs -r sudo docker network rm

# Prune everything else (build caches)
echo -e "\n🧹 Pruning system to free space..."
sudo docker system prune -af --volumes

# Final status
echo -e "\n✅ Docker cleanup complete."

# Show freed space information
echo -e "\n📊 Disk usage summary:"
df -h /

echo -e "\n🐳 Docker info (if service is running):"
sudo systemctl start docker.socket docker.service || true
sudo docker info || true

echo -e "\n✨ DONE."
