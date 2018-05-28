import paho.mqtt.client as mqtt
import time
mqtt_client = mqtt.Client("pigfucker")
mqtt_client.connect("dantalion", port=1883, keepalive=30, bind_address="")
mqtt_client.subscribe("#")

def on__message(client, userdata, message):
    print(message.topic)


mqtt_client.on_message = on__message
mqtt_client.loop_forever(timeout=111.0, max_packets=1, retry_first_connection=True)

