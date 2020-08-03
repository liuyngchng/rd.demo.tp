cout << perf.mbpsSendRate << ","
        << perf.msRTT << ","
        << perf.pktCongestionWindow << ","
        << perf.usPktSndPeriod << ","
        << perf.pktRecvACK << ","
        << perf.pktRecvNAK << ","
        << perf.pktSent << ","
        << perf.pktRecv << ","
        << perf.pktSndLoss << ","
        << perf.pktRcvLoss << ","
        << perf.pktRetrans << ","
        << perf.pktSentACK << ","
        << perf.pktRecvACK << ","
        << perf.pktSentNAK << ","
        << perf.pktRecvNAK << ","
        << perf.usSndDuration << ","
        << perf.pktSentTotal << ","
        << perf.pktRecvTotal << ","
        << perf.pktSndLossTotal << ","
        << perf.pktRcvLossTotal << ","
        << perf.pktRetransTotal << ","
        << perf.pktSentACKTotal << ","
        << perf.pktRecvACKTotal << ","
        << perf.pktSentNAKTotal << ","
        << perf.pktRecvNAKTotal << ",";
       printf("%lu,", perf.usSndDurationTotal);
       printf("%lu\r\n", perf.usSndDurationTotal);


