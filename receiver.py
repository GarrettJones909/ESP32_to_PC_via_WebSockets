import asyncio
import websockets
import json

# Set the WebSocket server address and port
HOST = "0.0.0.0"  # Listen on all available network interfaces
PORT = 8765       # Choose any open port

connected_clients = set()  # Track connected ESP32 clients

async def handle_client(websocket, path = None):
    print("ESP32 connected!")
    connected_clients.add(websocket)

    try:
        async for message in websocket:
            try:
                data = json.loads(message)
                print(f"Received LiDAR Distance: {data['distance']} meters")
            except:
                print(f"Received data from ESP32: {message}")

            # Example: Send a command back
            #command = input("Enter command for ESP32: ")
            command = "Hello from the PC!"
            await asyncio.sleep(0.5)
            await websocket.send(command)
            print(f"Sent: {command}")
            

    except websockets.exceptions.ConnectionClosed:
        print("ESP32 disconnected!")
    finally:
        connected_clients.remove(websocket)

# Start WebSocket server
async def main():
    server = await websockets.serve(handle_client, HOST, PORT)
    print(f"WebSocket Server running on ws://{HOST}:{PORT}")
    await server.wait_closed()

# Run the WebSocket server
asyncio.run(main())
