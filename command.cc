/*
 * ampduino protocol
 *
 * This is intended to be added to your project and kept up to date with upstream.
 *
 * All devices must speak the same version of protocol.
 *
 * Protocol is subject to completely change rapidly right now.
 *
 * XXX: Break this up so that it can be included in either ampduino or
 * XXX: an ampduino connected arduino sketch.
 */
#include <string.h>
#include "ampduino.h"

#define	ERR_PACKET_SIZE		-1000	// Packet size invalid
#define	ERR_BAD_CHECKSUM 	-1001	// Packet checksum invalid
#define ERR_NYI			-9999	// Not Yet Implemented

////
// XXX: These need to hook up to the other modules, to allow streamlining an img
////
int cmd_reboot(const char *packet) {
    return ERR_NYI;
}

int cmd_power(const char *packet) {
    return ERR_NYI;
}

int cmd_ptt(const char *packet) {
    return ERR_NYI;
}

int cmd_ptt_end(const char *packet) {
    return ERR_NYI;
}


int cmd_status(const char *packet) {
    return ERR_NYI;
}


int cmd_tx_ok(const char *packet) {
    return ERR_NYI;
}

int cmd_tx_halt(const char *packet) {
    return ERR_NYI;
}

int cmd_rotor_read(const char *packet) {
    return ERR_NYI;
}

int cmd_rotor_rotate(const char *packet) {
    return ERR_NYI;
}

int cmd_switch_in(const char *packet) {
    return ERR_NYI;
}

int cmd_switch_out(const char *packet) {
    return ERR_NYI;
}

int cmd_tuner_tune(const char *packet) {
    return ERR_NYI;
}

AmpduinoNoun cmd_nouns[] = {
    { "*",	DEVTYPE_ANY },
    { "AMP",	DEVTYPE_AMPLIFIER },
    { "FLT", 	DEVTYPE_FILTER },
    { "RAD",	DEVTYPE_RADIO },
    { "ROT",	DEVTYPE_ROTOR },
    { "SW",	DEVTYPE_SWITCH },
    { "TNR",	DEVTYPE_TUNER },
    { "TV",	DEVTYPE_TRANSVERTER },
    { (char *)NULL, 0 }
};

AmpduinoCommand cmds_common[] = {
    { "BOOT",	.cmd_type = CMD_MODAL, .hook = cmd_reboot },
    { "POWER",	.cmd_type = CMD_MODAL, .hook = cmd_power },
    { "PTT",	.cmd_type = CMD_ACTION, .hook = cmd_ptt },
    { "PTT_END", .cmd_type = CMD_ACTION, .hook = cmd_ptt_end },
    { "STATUS", .cmd_type = CMD_STATUS, .hook = cmd_status },
    { "TX_OK",	.cmd_type = CMD_STATUS, .hook = cmd_tx_ok },
    { "TX_HALT", .cmd_type = CMD_MODAL, .hook = cmd_tx_halt },
    // tuner: Tune
    { "TUNE",	.cmd_type = CMD_ACTION, .hook = cmd_tuner_tune, .valid_verbs = DEVTYPE_TUNER },
    // switch: Set Input
    { "IN",	.cmd_type = CMD_ACTION, .hook = cmd_switch_in, .valid_verbs = DEVTYPE_SWITCH },
    // switch: Set Output
    { "OUT",	.cmd_type = CMD_ACTION, .hook = cmd_switch_out, .valid_verbs = DEVTYPE_SWITCH },
    // rotor: Read position
    { "READ",	.cmd_type = CMD_STATUS, .hook = cmd_rotor_read, .valid_verbs = DEVTYPE_ROTOR },
    // rotor: Set position
    { "ROTATE",	.cmd_type = CMD_ACTION, .hook = cmd_rotor_rotate, .valid_verbs = DEVTYPE_ROTOR },
    { NULL, NULL, NULL }
};

// Size limits for the packet
#define	MIN_PKTLEN 24
#define	MAX_PKTLEN 64

//////////////////////////////
// Verify packet's checksum //
//////////////////////////////
int pkt_verify_checksum(const char *buf) {
  return 0;
}

// Parse an incoming protocol packet from the serial line
int ampduino_parse(const char *buf) {
    // Pointers to important places in buffer
    const char *src, *dst, *cmd_type, *cmd, *s_seqno, *s_noun, *s_flags;

    if (strlen(buf) < MIN_PKTLEN) {
      // Abort if too big
      return ERR_PACKET_SIZE;
    } else if (strlen(buf) > MAX_PKTLEN) {
      return ERR_PACKET_SIZE;
    }

    // XXX: Verify checksum
    if (pkt_verify_checksum(buf) != 0) {
       return ERR_BAD_CHECKSUM;
    }

    // XXX: Create pointers to offsets within the packet
    src = buf[0];
    dst = buf[1];
    s_seqno = buf[2];
    s_flags = buf[7];
//    cmd = parse_cmd_type(buf[10]);

    // XXX: Make sure pointers are sane
    // XXX: Push values into a packet structure
    // XXX: Call appropriate function with packet
    return 0;
}

////////////////////////
// Construct a packet //
////////////////////////
int ampduino_send_msg(const unsigned int src, const unsigned int dest, const char *msg) {
    AmpduinoPacket pkt;

    memset(&pkt, 0, sizeof(AmpduinoPacket));

    if (src > 0)
       pkt.src = src;
    else
       pkt.src = CF_RAN_ADDRESS;

    pkt.dest = dest;

    
    return 0;
}
