/**
 * PPRetailInvoiceTemplate.h
 *
 * DO NOT EDIT THIS FILE! IT IS AUTOMATICALLY GENERATED AND SHOULD NOT BE CHECKED IN.
 * Generated from: node_modules/paypal-invoicing/lib/Template.js
 *
 * 
 */

#import "PayPalRetailSDKTypeDefs.h"
#import "PPRetailObject.h"
#import "PPRetailInvoice.h"

@class PPRetailSDK;
@class PPRetailError;
@class PPRetailPayPalErrorInfo;
@class PPRetailAccountSummary;
@class PPRetailAccountSummarySection;
@class PPRetailInvoiceAddress;
@class PPRetailInvoiceAttachment;
@class PPRetailInvoiceBillingInfo;
@class PPRetailInvoiceCCInfo;
@class PPRetailCountries;
@class PPRetailCountry;
@class PPRetailInvoiceCustomAmount;

@class PPRetailInvoiceActions;
@class PPRetailInvoiceConstants;
@class PPRetailInvoiceListRequest;
@class PPRetailInvoiceListResponse;
@class PPRetailInvoiceMetaData;
@class PPRetailInvoiceTemplatesResponse;
@class PPRetailInvoicingService;
@class PPRetailInvoiceItem;
@class PPRetailInvoiceMerchantInfo;
@class PPRetailInvoiceNotification;
@class PPRetailInvoicePayment;
@class PPRetailInvoicePaymentTerm;
@class PPRetailInvoiceRefund;
@class PPRetailInvoiceSearchRequest;
@class PPRetailInvoiceShippingInfo;
@class PPRetailInvoiceTemplate;
@class PPRetailInvoiceTemplateSettings;
@class PPRetailMerchant;
@class PPRetailNetworkRequest;
@class PPRetailNetworkResponse;
@class PPRetailSdkEnvironmentInfo;
@class PPRetailRetailInvoice;
@class PPRetailRetailInvoicePayment;
@class PPRetailTokenExpirationHandler;
@class PPRetailTransactionContext;
@class PPRetailTransactionBeginOptions;
@class PPRetailReceiptDestination;
@class PPRetailDeviceManager;
@class PPRetailSignatureReceiver;
@class PPRetailReceiptOptionsViewContent;
@class PPRetailReceiptEmailEntryViewContent;
@class PPRetailReceiptSMSEntryViewContent;
@class PPRetailReceiptViewContent;
@class PPRetailCard;
@class PPRetailBatteryInfo;
@class PPRetailMagneticCard;
@class PPRetailPaymentDevice;
@class PPRetailManuallyEnteredCard;
@class PPRetailDeviceUpdate;
@class PPRetailCardInsertedHandler;
@class PPRetailDeviceStatus;
@class PPRetailPayer;
@class PPRetailTransactionRecord;
@class PPRetailCaptureResponse;
@class PPRetailAuthorizedTransaction;
@class PPRetailRetrieveAuthorizedTransactionResponse;
@class PPRetailPage;
@class PPRetailDiscoveredCardReader;
@class PPRetailCardReaderScanAndDiscoverOptions;
@class PPRetailDeviceConnectorOptions;


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/**
 * Invoice template
 */
@interface PPRetailInvoiceTemplate : PPRetailInvoice

    /**
    * true if this is the default template
    */
    @property (nonatomic,assign) BOOL isDefault;
    /**
    * true if this is a custom template
    */
    @property (nonatomic,assign) BOOL isCustom;
    /**
    * name of the template
    */
    @property (nonatomic,strong,nullable) NSString* name;
    /**
    * unit of measure for the template,
 * known values: AMOUNT, QUANTITY, HOURS
    */
    @property (nonatomic,strong,nullable) NSString* unitOfMeasure;
    /**
    * list of which fields are enabled/disabled
    */
    @property (nonatomic,strong,nullable) PPRetailInvoiceTemplateSettings* settings;


    
      - (instancetype _Nullable)initWithCurrencyCode:(NSString* _Nullable)currencyCode;
      
    - (instancetype _Null_unspecified)init NS_UNAVAILABLE;
    + (instancetype _Null_unspecified)new NS_UNAVAILABLE;




    /**
     * Return an invoice with all the fields from the template but the invoice
     * number and paypalID of another invoice
     */
    -(PPRetailInvoice* _Nullable)invoiceFromInvoice:(PPRetailInvoice* _Nullable)invoice;




@end
