package com.rfid;

import com.module.interaction.DataPackageProcess;
import com.rfid.bean.MessageTran;

/**
 * The implementation class of DataPackageProcess.
 */

public class ReaderDataPackageProcess extends DataPackageProcess {
    @Override
    public void analyData(byte[] btPackage) {
        MessageTran msgTran = new MessageTran(btPackage);
        if (msgTran != null) {
            setChanged();
            notifyObservers(msgTran);
        }
    }
}
