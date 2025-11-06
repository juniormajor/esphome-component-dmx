## ESPHome Integration

Diese Bibliothek kann direkt als External Component in [ESPHome](https://esphome.io) eingebunden werden.

### Verwendung in YAML

```yaml
external_components:
  - source: github://juniormajor/esp_dmx
    components: [dmx]

dmx:
  tx_pin: GPIO17
  rx_pin: GPIO16
  enable_pin: GPIO4
```

Stelle sicher, dass dein Repository diese Struktur enthält:

```
esphome/components/dmx/
├─ __init__.py
├─ dmx.h
├─ dmx.cpp
└─ dmx.yaml
```

Nach dem Commit kannst du ESPHome einfach neu kompilieren.
