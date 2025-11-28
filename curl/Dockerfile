# Use Ubuntu base
FROM ubuntu:24.04

# Install required packages
RUN apt-get update && \
    apt-get install -y g++ cmake libasio-dev && \
    apt-get clean

# Copy source code
COPY server.cpp /app/server.cpp

# Build the app
RUN g++ /app/server.cpp -o /app/server -pthread

# Expose port 8080 (Render uses PORT env variable)
EXPOSE 8080

# Run the server
CMD ["/app/server"]
