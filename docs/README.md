
A lot of interesting articles at [1]

### Guides

Short instructions

#### How to get into AT mode

1. Upload serial-passthrough to your MCU
2. Connect to the bluetooth with Phone/another HC-05 to make sure that
   communication works
3. Put PIO11 high. Device will stop to reponse on serial link
4. Put RESET pin low
5. Put RESET pin high
6. Now you are in AT mode. Configure HC-05
7. Put PIO11 low
8. Reset chip again

### Notes

#### HC-Status PIO9

Seems to work but with delays.

### References

[1]: https://www.microchip.com/wwwproducts/en/ATSHA204A
