#include <Arduino.h>
#include <active_object.h>

#define HELLO_EVENT 0x01

Active object;

bool custom_dispatcher(Event *ev, void *args)
{
    switch (ev->event_type)
    {
    case HELLO_EVENT:
        Serial.println("Hello world!");
        return true;
    }

    return false;
}

void setup()
{
    Serial.begin(9600);

    delay(2000);

    Serial.println("Ello govner'");

    delay(1000);

    object.dispatcher = custom_dispatcher;
    object.task_name = "HelloObject";
    object.queue = xQueueCreate(20, sizeof(Event));

    active_object_start(&object);
}

void loop()
{
    Event ev;

    ev.event_type = HELLO_EVENT;

    active_object_post(&object, ev);
    delay(2000);
}